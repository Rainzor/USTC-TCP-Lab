#include "router.hh"

#include <iostream>

using namespace std;

// Dummy implementation of an IP router

// Given an incoming Internet datagram, the router decides
// (1) which interface to send it out on, and
// (2) what next hop address to send it to.

// For Lab 6, please replace with a real implementation that passes the
// automated checks run by `make check_lab6`.

// You will need to add private members to the class declaration in `router.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

//! \param[in] route_prefix The "up-to-32-bit" IPv4 address prefix to match the datagram's destination address against
//! \param[in] prefix_length For this route to be applicable, how many high-order (most-significant) bits of the route_prefix will need to match the corresponding bits of the datagram's destination address?
//! \param[in] next_hop The IP address of the next hop. Will be empty if the network is directly attached to the router (in which case, the next hop address should be the datagram's final destination).
//! \param[in] interface_num The index of the interface to send the datagram out on.
// 接受一个路由表项，将其添加到路由表中
void Router::add_route(const uint32_t route_prefix,
                       const uint8_t prefix_length,
                       const optional<Address> next_hop,
                       const size_t interface_num) {
    cerr << "DEBUG: adding route " << Address::from_ipv4_numeric(route_prefix).ip() << "/" << int(prefix_length)
         << " => " << (next_hop.has_value() ? next_hop->ip() : "(direct)") << " on interface " << interface_num << "\n";

    _radixTree.insert(route_prefix, prefix_length, next_hop, interface_num);

}

//! \param[in] dgram The datagram to be routed
// 将一个数据报发送到下一个路由器：确认发送接口以及下一跳的 IP 地址
void Router::route_one_datagram(InternetDatagram &dgram) {
    const uint32_t dst_ip = dgram.header().dst;
    string ip_str = mask_to_string(dst_ip, 32);
    auto max_matched_router = _radixTree.search(ip_str);
    if(dgram.header().ttl-- > 1 ){
        const optional<Address> &next_hop = max_matched_router.next_hop;
        auto &interface = _interfaces[max_matched_router.interface_num];
        if(next_hop.has_value()){
            interface.send_datagram(dgram, next_hop.value());
        }else{
            interface.send_datagram(dgram, Address::from_ipv4_numeric(dst_ip));
        }

    }
   
}

void Router::route() {
    // Go through all the interfaces, and route every incoming datagram to its proper outgoing interface.
    for (auto &interface : _interfaces) {
        auto &queue = interface.datagrams_out();
        while (not queue.empty()) {
            route_one_datagram(queue.front());
            queue.pop();
        }
    }
}