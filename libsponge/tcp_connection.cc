#include "tcp_connection.hh"

#include <iostream>

// Dummy implementation of a TCP connection

// For Lab 4, please replace with a real implementation that passes the
// automated checks run by `make check`.

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

// 发送器剩余容量
size_t TCPConnection::remaining_outbound_capacity() const { 
    return _sender.stream_in().remaining_capacity();    
}

// 发送器已发送但未确认的字节数
size_t TCPConnection::bytes_in_flight() const { 
    return _sender.bytes_in_flight(); 
}

// 接收器未组装的字节数
size_t TCPConnection::unassembled_bytes() const { 
    return _receiver.unassembled_bytes();
}
// 接收上一个包至今的时间，用于判断是否超时
size_t TCPConnection::time_since_last_segment_received() const {
    return _time_since_last_segment_received_ms;
}

// 处理接收到的段
void TCPConnection::segment_received(const TCPSegment &seg) {
    _time_since_last_segment_received_ms = 0;

    // 接收器处理接收到的段
    // 它将对数据包中的 seqno、SYN、payload、FIN 进行处理
    _receiver.segment_received(seg);
    auto ackno = _receiver.ackno();

    // 如果接受的包含有RST，结束会话
    if(seg.header().rst){
        _set_rst_state(false);//非法结束
        return;
    }

    // 用seg的实际长度+SYN+FIN判断是否需要发送ACK
    // 如果接受到的是空包（ACK包）则不用发送，即没有ACK_ACK
    bool is_send_empty = seg.length_in_sequence_space();
    bool is_ack_received = true;
    // 如果接受的包含有ACK，发送器需要处理字段
    if(seg.header().ack){//除了SYN包，其他包都会有ACK字段
        //判断接收到的ack是否合法,并更新发送器内部信息，组装数据包，填充窗口
        is_ack_received =  _sender.ack_received(seg.header().ackno, seg.header().win);
        // 如果_sender.segments_out()不为空，说明有数据需要发送,则不需要发送空的ACK包
        is_send_empty &= _sender.segments_out().empty();
    }
    
    // 接收器处于SYN_RECV状态，发送器处于CLOSED状态
    if (TCPState::state_summary(_sender) == TCPSenderStateSummary::CLOSED&&
        TCPState::state_summary(_receiver) == TCPReceiverStateSummary::SYN_RECV) {
        connect();//建立连接，发送SYN+ACK
        return;
    }
    
    // TCP断开后是否需要等待，需要保证收到了对方的FIN包，同时自己已发送FIN
    // CLOSE CONDITION1:输入流的报文已经结束并全部组装完毕
    // CLOSE CONDITION2:输出流的报文已经结束并且已经全部发送给对方（包括 FIN）
    if(TCPState::state_summary(_sender) == TCPSenderStateSummary::SYN_ACKED&&
        TCPState::state_summary(_receiver) == TCPReceiverStateSummary::FIN_RECV){
        _linger_after_streams_finish = false;
    }

    // TCP准备断开时，需要保证发送的FIN包已经被确认，且收到了对方的FIN
    // CLOSE CONDITION3: 收到了远程方的确认 ack
    if (TCPState::state_summary(_sender) == TCPSenderStateSummary::FIN_ACKED && 
        TCPState::state_summary(_receiver) == TCPReceiverStateSummary::FIN_RECV &&
        !_linger_after_streams_finish) {
        _is_active = false;
        return;
    }
    
    if (ackno.has_value()){   
        const TCPHeader &seg_header = seg.header();
        // Keep-alive 判断
        is_send_empty |=  (seg.length_in_sequence_space() == 0)&& (seg_header.seqno == ackno.value() - 1);
        // 非法seg.seqno
        uint64_t abs_receviver_ack = _receiver.assembled_bytes()+1;
        uint64_t abs_seg_seqno = unwrap(seg_header.seqno, _receiver.isn(), abs_receviver_ack);
        is_send_empty |=  _receiver.window_size()&&(abs_seg_seqno >= abs_receviver_ack + _receiver.window_size());
        // 非法seg.ackno
        is_send_empty |= seg.header().ack&& !is_ack_received;
    }
    if(is_send_empty){//确实需要回复ack，sender添加空的ACK包
        _sender.send_empty_segment();
    }
    _trans_segments_to_out_with_ack_and_win();
}

bool TCPConnection::active() const { 
    return _is_active;
}

// 向Sender内部添加数据，来自应用层
size_t TCPConnection::write(const string &data) {
    size_t write_len = _sender.stream_in().write(data);
    _sender.fill_window();//将待发送的数据尽可能的填充到窗口中
    _trans_segments_to_out_with_ack_and_win();//从sender中转移到输出队列中
    return write_len;
}

void TCPConnection::tick(const size_t ms_since_last_tick) { 
    _sender.tick(ms_since_last_tick);
    // 接收器超过了最大的重传次数，发送RST
    if(_sender.consecutive_retransmissions() > TCPConfig::MAX_RETX_ATTEMPTS){
        // 清空待发送的数据，准备重传
        while (!_sender.segments_out().empty())
            _sender.segments_out().pop();
        _set_rst_state(true);
        return;
    }
    // 重传
    _trans_segments_to_out_with_ack_and_win();

    // 更新时间
    _time_since_last_segment_received_ms += ms_since_last_tick;
    // 如果接收器处于FIN_RECV状态，且接收器的流已经结束，且发送器的流已经结束
    // 等待10个RTT后，结束会话
    if(TCPState::state_summary(_sender) == TCPSenderStateSummary::FIN_ACKED && 
        TCPState::state_summary(_receiver) == TCPReceiverStateSummary::FIN_RECV &&
        _linger_after_streams_finish && 
        _time_since_last_segment_received_ms >= 10 * _cfg.rt_timeout){
        _is_active = false;
        _linger_after_streams_finish = false;
    }
}

void TCPConnection::end_input_stream() {
    _sender.stream_in().end_input();//不再接受上层数据
    _sender.fill_window();
    _trans_segments_to_out_with_ack_and_win();
}

void TCPConnection::connect() {
    _is_active = true;
    _sender.fill_window();//第二次握手
    _trans_segments_to_out_with_ack_and_win();
}

TCPConnection::~TCPConnection() {
    try {
        if (active()) {
            cerr << "Warning: Unclean shutdown of TCPConnection\n";
            _set_rst_state(true);
        }
    } catch (const exception &e) {
        std::cerr << "Exception destructing TCP FSM: " << e.what() << std::endl;
    }
}

void TCPConnection::_set_rst_state(bool send_rst) {
    if (send_rst) {
        TCPSegment rst_seg;
        rst_seg.header().rst = true;
        _segments_out.push(rst_seg);
    }
    _receiver.stream_out().set_error();
    _sender.stream_in().set_error();
    _linger_after_streams_finish = false;
    _is_active = false;
}

//将sender中待发送的字段转移到输出队列中，并添加ACK和window size字段
void TCPConnection::_trans_segments_to_out_with_ack_and_win() {
    // 等待发送的数据包头添加本地的 ACK 和 window size
    // 随着字段一起发送
    while (!_sender.segments_out().empty()) {
        TCPSegment seg = _sender.segments_out().front();
        _sender.segments_out().pop();
        if (_receiver.ackno().has_value()) {
            seg.header().ack = true;
            seg.header().ackno = _receiver.ackno().value();
            seg.header().win = _receiver.window_size();
        }
        _segments_out.push(seg);
    }
}

