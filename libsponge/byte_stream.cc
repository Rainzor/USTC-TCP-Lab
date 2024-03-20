#include "byte_stream.hh"

#include <algorithm>
#include <iterator>
#include <stdexcept>

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;


// TODO
ByteStream::ByteStream(const size_t capacity) { 
    _capacity = capacity;
    _write_count = 0;
    _read_count = 0;
    _input_ended_flag = false;
    _error = false;
 }

//将data写入BufferStream, 不超过最大容量
size_t ByteStream::write(const string &data) {
    auto ret = min(data.size(), remaining_capacity());
    string s = data.substr(0, ret);
    _buffer.append(BufferList(move(s)));
    _write_count += ret;
    return ret;
}


//! \param[in] len bytes will be copied from the output side of the buffer
// 从BufferStream中读取len个字节, 不超过Buffer当前大小
string ByteStream::peek_output(const size_t len) const {
    auto n = min(len, _buffer.size());
    string ret = _buffer.concatenate();
    return ret.substr(0, n);
}

//! \param[in] len bytes will be removed from the output side of the buffer
// 从BufferStream中删除len个字节
void ByteStream::pop_output(const size_t len) { 
    auto n = min(len, _buffer.size());
    _buffer.remove_prefix(n);
    _read_count += n;
}
// 从BufferStream中读取len个字节,并删除
std::string ByteStream::read(const size_t len) {
    const auto ret = peek_output(len);
    pop_output(len);
    return ret;
}

void ByteStream::end_input() { _input_ended_flag = true; }

bool ByteStream::input_ended() const { return _input_ended_flag; }

size_t ByteStream::buffer_size() const { return _buffer.size(); }

bool ByteStream::buffer_empty() const { return _buffer.size() == 0;}

bool ByteStream::eof() const { return _input_ended_flag && buffer_empty(); }

size_t ByteStream::bytes_written() const { return  _write_count; }

size_t ByteStream::bytes_read() const { return _read_count; }

size_t ByteStream::remaining_capacity() const { 
    return _capacity-_buffer.size();    
}
