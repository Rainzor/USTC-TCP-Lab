#include "socket.hh"
#include "util.hh"
#include <cstdlib>
#include <iostream>

using namespace std;
int main()
{
    TCPSocket sock{};
    sock.connect(Address("127.0.0.1", "ssh"));
    sock.write("SSH");
    sock.shutdown(SHUT_WR);
    while(!sock.eof()){
        cout << sock.read();
    }
    sock.close();
}