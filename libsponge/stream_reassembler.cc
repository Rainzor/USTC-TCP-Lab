#include "stream_reassembler.hh"

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity) : _unass_base(0), _unass_size(0),
                                                              _output(capacity), _capacity(capacity),
                                                              _eof(false), _eof_idx(0) {}

// 新插入的数据可能会与原有的数据重叠，要将数据进行合并
// 其中输入的index, data.len 都是合法的，在剩余窗口范围内
void StreamReassembler::insert_merge(const size_t &index, const string &data)
{
    size_t len = data.length();
    if (len == 0)
        return;
    size_t begin = index;
    size_t end = index + len;
    string merge_data = data;

    std::vector<std::map<size_t, std::string>::iterator> it_destory_vec{};
    for (auto it = _window.begin(); it != _window.end(); it++)
    {
        size_t it_end = it->first + it->second.length();

        if (it_end <= index)
            continue;

        if (it->first <= index && it_end >= end)
        {
            return;
        }

        if ((it->first >= index && it_end < end) || (it->first > index && it_end <= end))
        {
            it_destory_vec.push_back(it);
        }

        if (it->first < index && it_end > index && it_end < end)
        {
            merge_data = it->second.substr(0, it_end - index) + merge_data;
            begin = it->first;
            it_destory_vec.push_back(it);
        }

        if (it->first > index && it->first < end && it_end > end)
        {
            merge_data = merge_data.substr(0, it->first - index) + it->second;
            it_destory_vec.push_back(it);
            break;
        }
    }
    for (auto it : it_destory_vec)
    {
        _unass_size -= it->second.length();
        _window.erase(it);
    }
    _window[begin] = merge_data;
    _unass_size += merge_data.length();
}

// 只有当_unass_base处存在windows中时才会重组
void StreamReassembler::reassemble_stream()
{
    auto it = _window.begin();

    while (it != _window.end() && it->first == _unass_base)
    {
        // size_t offset = _unass_base - it->first;
        // size_t writed_len = it->second.length() - offset;
        // _output.write(it->second.substr(offset, writed_len));
        size_t writed_len = _output.write(it->second);
        _unass_base += writed_len;
        _unass_size -= writed_len;
        it = _window.erase(it);
    }
    _window.erase(_window.begin(), it);
}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.

void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof)
{
    if (eof)
    {
        _eof = true;
        _eof_idx = index + data.length();
    }
    size_t len = data.length();

    if (index >= _unass_base + _output.remaining_capacity()) // 越界
        return;

    if (index >= _unass_base)
    {
        size_t buf_offset = index - _unass_base;
        // 待写入的数据不能超过窗口范围
        size_t real_len = min(len, _output.remaining_capacity() - buf_offset);
        if (real_len < len)
            _eof = false;
        insert_merge(index, data.substr(0, real_len));
    }
    else if (index + len > _unass_base)
    { // index <= _unass_base
        size_t str_offset = _unass_base - index;
        // 待写入的数据不能超过窗口范围
        size_t real_len = min(len - str_offset, _output.remaining_capacity());
        if (real_len < len - str_offset)
            _eof = false;
        insert_merge(_unass_base, data.substr(str_offset, real_len));
    } // else index+len <= _unass_base
    reassemble_stream();
    if (_eof && _eof_idx <= _unass_base)
    {
        _output.end_input();
    }
}

size_t StreamReassembler::unassembled_bytes() const { return _unass_size; }

bool StreamReassembler::empty() const { return _unass_size == 0; }
