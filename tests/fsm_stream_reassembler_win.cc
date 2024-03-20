#include "byte_stream.hh"
#include "stream_reassembler.hh"
#include "util.hh"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

static constexpr unsigned NREPS = 32;
static constexpr unsigned NSEGS = 128;
static constexpr unsigned MAX_SEG_LEN = 2048;
string read(StreamReassembler &reassembler) {
    return reassembler.stream_out().read(reassembler.stream_out().buffer_size());
}

int main() {
    try {
        auto rd = get_random_generator();

        // overlapping segments
        for (unsigned rep_no = 0; rep_no < NREPS; ++rep_no) {
            StreamReassembler buf{NSEGS * MAX_SEG_LEN};

            vector<tuple<size_t, size_t>> seq_size;
            size_t offset = 0;
            for (unsigned i = 0; i < NSEGS; ++i) {
                const size_t size = 1 + (rd() % (MAX_SEG_LEN - 1));
                const size_t offs = min(offset, 1 + (static_cast<size_t>(rd()) % 1023));
                seq_size.emplace_back(offset - offs, size + offs);
                offset += size;
            }
            shuffle(seq_size.begin(), seq_size.end(), rd);

            string d(offset, 0);
            // generate(d.begin(), d.end(), [&] { return rd(); });
            generate(d.begin(), d.end(), [&]
                     {
                         char c = rd() % 52; // 生成一个0到51的随机数
                         if (c < 26)
                             return 'A' + c; // 将0到25映射到大写字母A到Z
                         else
                             return 'a' + (c - 26); // 将26到51映射到小写字母a到z
                     });

            // printf("\n -------------------\n");
            for (auto [off, sz] : seq_size) {
                string dd(d.cbegin() + off, d.cbegin() + off + sz);
                // printf("off = %lu, sz = %lu, end = %lu\n", off, sz, off + sz );
                // printf("%s\n", dd.c_str());
                // printf("assemble:\n");
                buf.push_substring(move(dd), off, off + sz == offset);
                // buf.stream_out().print();
            }

            auto result = read(buf);
            // printf("result.size() = %lu\n", result.size());
            // printf("%s\n", result.c_str());
            // printf("d.size() = %lu\n", d.size());
            // printf("%s\n", d.c_str());
            // printf("buf.stream_out().bytes_written() = %lu\n", buf.stream_out().bytes_written());
            // printf("offset = %lu\n", offset);
            // printf("unassemble bytes = %lu\n", buf.unassembled_bytes());
            // printf("assembled bytes = %lu\n", buf.assembled_bytes());
            // printf("_eof_idx = %lu\n", buf.stream_size());
            if (buf.stream_out().bytes_written() != offset) {  // read bytes
                throw runtime_error("test 3 - number of RX bytes is incorrect");
            }
            if (!equal(result.cbegin(), result.cend(), d.cbegin())) {
                throw runtime_error("test 3 - content of RX bytes is incorrect");
            }
        }
    } catch (const exception &e) {
        cerr << "Exception: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
