#include "tcp_sender.hh"

#include "tcp_config.hh"

#include <random>

// Dummy implementation of a TCP sender

// For Lab 3, please replace with a real implementation that passes the
// automated checks run by `make check_lab3`.

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

//! \param[in] capacity the capacity of the outgoing byte stream
//! \param[in] retx_timeout the initial amount of time to wait before retransmitting the oldest outstanding segment
//! \param[in] fixed_isn the Initial Sequence Number to use, if set (otherwise uses a random ISN)
TCPSender::TCPSender(const size_t capacity, const uint16_t retx_timeout, const std::optional<WrappingInt32> fixed_isn)
    : _isn(fixed_isn.value_or(WrappingInt32{random_device()()}))
    , _initial_retransmission_timeout{retx_timeout}
    , _stream(capacity) {}

//已经发送的但还未收到ACK确认的字节数目
uint64_t TCPSender::bytes_in_flight() const { return _out_bytes; }

//填满远程的窗口
void TCPSender::fill_window() {
    //当远程window size=0时，任然视作1，防止sender中断
    size_t cur_win_sz = _last_win_sz ? _last_win_sz : 1;

    //尽可能的填充窗口
    while( cur_win_sz > bytes_in_flight()){
        TCPSegment seg;

        //处理SYN
        if(!is_syn){
            seg.header().syn = true;
            is_syn = true;
        }
        // next_seqno() 是warp后的序号
        // _next_seqno 是绝对序号
        seg.header().seqno = next_seqno();

        //发送数据大小：
        //1. 不能超过最大payload大小
        //2. 尽可能的填满window，
        //   但不能记上已经发送但未组装的数据，这部分数据可能乱序的排布在windows中
        //3. 如果有SYN，则SYN占据一个字节
        size_t payload_size = min(TCPConfig::MAX_PAYLOAD_SIZE,
                                cur_win_sz - bytes_in_flight() - seg.header().syn);
        // 读取数据
        string payload_str = _stream.read(payload_size);

        //处理FIN
        //当读取到文件末尾时，且没有发送过FIN
        //当装填数据大小和已经发送的数据不超过当前窗口大小时，
        //把FIN和数据一起发送
        if (!is_fin && _stream.eof()) {
            if (payload_str.size() < cur_win_sz - bytes_in_flight()) {
                seg.header().fin = true;
                is_fin = true;
            }
        }

        seg.payload() = Buffer(std::move(payload_str));


        //seg.length_in_sequence_space()是记上syn,fin的长度的
        size_t seg_len = seg.length_in_sequence_space();
        if (seg_len == 0) { // 没有数据待发送
            break;
        }

        //重置时间：只发生在发送的seg被读取完毕
        if(_segments_inflight.empty()){
            _timeout = _initial_retransmission_timeout;
            _timecount = 0;
        }

        _out_bytes += seg_len;
        // _seg_out_map[_next_seqno]= seg;
        _segments_inflight.push_back(seg);

        _segments_out.push(seg);
        _next_seqno += seg_len;

        if(seg.header().fin){
            break;
        }
    }
}

//! \param ackno The remote receiver's ackno (acknowledgment number)
//! \param window_size The remote receiver's advertised window size
//! \returns `false` if the ackno appears invalid (acknowledges something the TCPSender hasn't sent yet)
bool TCPSender::ack_received(const WrappingInt32 ackno, const uint16_t window_size) {
    size_t abs_ack_no = unwrap(ackno, _isn, _next_seqno);
    if(abs_ack_no > _next_seqno){//非法的ack
        return false;
    }
    //处理 bytes in flight
    while(!_segments_inflight.empty()){
        auto &seg = _segments_inflight.front();
        size_t seg_len = seg.length_in_sequence_space();
        uint64_t abs_sqe_no = unwrap(seg.header().seqno, _isn, _next_seqno);
        if(abs_sqe_no + seg_len <= abs_ack_no){
            _segments_inflight.pop_front();
            _out_bytes -= seg_len;
            _timeout = _initial_retransmission_timeout;
        }else
            break;
    }


    //重传计数器置0
    _retransmissions_count = 0;
    
    //更新窗口大小,传输新的数据
    _last_win_sz = window_size;
    fill_window();
    return true;
}

//! \param[in] ms_since_last_tick the number of milliseconds since the last call to this method
void TCPSender::tick(const size_t ms_since_last_tick) {
    _timecount += ms_since_last_tick;
    if(!_segments_inflight.empty()&&_timecount >= _timeout){
        _timeout *= 2;
        _timecount = 0;
        _retransmissions_count++;
        _segments_out.push(_segments_inflight.front());
    }
}

unsigned int TCPSender::consecutive_retransmissions() const { return _retransmissions_count; }

void TCPSender::send_empty_segment() {
    TCPSegment seg;
    seg.header().seqno = next_seqno();
    _segments_out.push(seg);
}
