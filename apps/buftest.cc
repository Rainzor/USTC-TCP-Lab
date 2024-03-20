#include "util/buffer.hh"
#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdexcept>
using namespace std;
int main()
{
    BufferList _buffer = {};//dequeue
    string s = "hello buffer";
    _buffer.append(BufferList(move(s)));//创建
    string s1 = _buffer.concatenate();//拷贝
    string s2;
    s2.assign(s1.begin(), s1.begin() + 5);
    _buffer.remove_prefix(5);
    s1 = _buffer.concatenate();
    
}