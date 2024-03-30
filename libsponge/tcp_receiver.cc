#include "tcp_receiver.hh"

// Dummy implementation of a TCP receiver

// For Lab 2, please replace with a real implementation that passes the
// automated checks run by `make check_lab2`.

template <typename... Targs> void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

bool TCPReceiver::segment_received(const TCPSegment &seg) {
    const TCPHeader &header = seg.header();
    uint64_t abs_ackno;
    uint64_t abs_seqno;
    uint64_t idx;
    switch (_state) {
    case LISTEN:
        if (header.syn) {
        _isn = header.seqno;
        _state = SYN_RECV;
        is_syn = true;
        _reassembler.push_substring(seg.payload().copy(), 0, header.fin);
        } else {
            return false;
        }
        break;
    case SYN_RECV:
        // 这里不能用buffer_size,因为buffer的内容随时可能被读取
        if (header.syn) {
            return false;
        }
        if (header.fin) {
            if (is_fin)
                return false;
            is_fin = true;
        }
        abs_ackno = _reassembler.assembled_bytes() + 1;
        abs_seqno = unwrap(header.seqno, _isn, abs_ackno); // 绝对序列号
        idx = abs_seqno - 1; // 从第一次发送的SYN序列开始，abs_seqno是0,占据了一个字节，真实的序列号是1
        if (seg.payload().size() > 0) {
            // 非法序列号
            if (abs_seqno + seg.payload().size() <= abs_ackno||
                abs_seqno >= abs_ackno + window_size()) {
                return false;
            }
        }
        // 向重组器中添加数据
        _reassembler.push_substring(seg.payload().copy(), idx, header.fin);
        if (_reassembler.stream_out().input_ended()) {
            // 所有数据都已经接收
            _state = FIN_RECV;
        }
        break;
    case FIN_RECV://处于FIN_RECV状态时，不接受任何数据
        return false;
    default:
        break;
    }
    return true;
}

// ackno() must be used after segment_received()
optional<WrappingInt32> TCPReceiver::ackno() const {
    if (_state == LISTEN) {
        return nullopt;
    }
    uint64_t abs_ackno = _reassembler.assembled_bytes() + 1;
    if (_reassembler.stream_out().input_ended()) {
        abs_ackno++; // FIN 占据一个字节
    }
    return wrap(abs_ackno, _isn);
}

size_t TCPReceiver::window_size() const { return _reassembler.windows_size(); }
