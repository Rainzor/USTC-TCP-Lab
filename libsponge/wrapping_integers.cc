#include "wrapping_integers.hh"

// Dummy implementation of a 32-bit wrapping integer

// For Lab 2, please replace with a real implementation that passes the
// automated checks run by `make check_lab2`.

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

//! Transform an "absolute" 64-bit sequence number (zero-indexed) into a WrappingInt32
//! \param n The input absolute 64-bit sequence number
//! \param isn The initial sequence number
WrappingInt32 wrap(uint64_t n, WrappingInt32 isn)
{
    uint32_t n32 = n & UINT32_MAX;
    WrappingInt32 seqno{n32 + isn.raw_value()}; // mod 2^32
    return seqno;
}

//! Transform a WrappingInt32 into an "absolute" 64-bit sequence number (zero-indexed)
//! \param n The relative sequence number
//! \param isn The initial sequence number
//! \param checkpoint A recent absolute 64-bit sequence number
//! \returns the 64-bit sequence number that wraps to `n` and is closest to `checkpoint`
//!
//! \note Each of the two streams of the TCP connection has its own ISN. One stream
//! runs from the local TCPSender to the remote TCPReceiver and has one ISN,
//! and the other stream runs from the remote TCPSender to the local TCPReceiver and
//! has a different ISN.
uint64_t unwrap(WrappingInt32 n, WrappingInt32 isn, uint64_t checkpoint)
{
    // absolute seqno = k * 2^32 + (n-isn)

    // 如果 real_offset = n.raw_value() - wrap(checkpoint,isn).raw_value() < 0
    // 那么此时计算的 offset = real_offset + 2^32

    // 通常 abs_n >= checkpoint
    uint32_t offset = n.raw_value() - wrap(checkpoint, isn).raw_value();
    uint64_t abs_seqno = checkpoint + offset;
    uint32_t UINT32_half = 1u << 31;
    uint64_t UINT32_max_add_1 = 1ul << 32;
    if (offset > UINT32_half && abs_seqno >= UINT32_max_add_1)
    {
        abs_seqno -= UINT32_max_add_1;
    }
    return abs_seqno;
}
