#include "network_interface.hh"

#include "arp_message.hh"
#include "ethernet_frame.hh"

#include <iostream>

// Dummy implementation of a network interface
// Translates from {IP datagram, next hop address} to link-layer frame, and from link-layer frame to IP datagram

// For Lab 5, please replace with a real implementation that passes the
// automated checks run by `make check_lab5`.

// You will need to add private members to the class declaration in `network_interface.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

//! \param[in] ethernet_address Ethernet (what ARP calls "hardware") address of the interface
//! \param[in] ip_address IP (what ARP calls "protocol") address of the interface
NetworkInterface::NetworkInterface(const EthernetAddress &ethernet_address, const Address &ip_address)
    : _ethernet_address(ethernet_address), _ip_address(ip_address) {
    cerr << "DEBUG: Network interface has Ethernet address " << to_string(_ethernet_address) << " and IP address "
         << ip_address.ip() << "\n";
}

//! \param[in] dgram the IPv4 datagram to be sent
//! \param[in] next_hop the IP address of the interface to send it to (typically a router or default gateway, but may also be another host if directly connected to the same network as the destination)
//! (Note: the Address type can be converted to a uint32_t (raw 32-bit IP address) with the Address::ipv4_numeric() method.)
void NetworkInterface::send_datagram(const InternetDatagram &dgram, const Address &next_hop) {
    // convert IP address of next hop to raw 32-bit representation (used in ARP header)
    // 将下一跳的IP地址转换为原始32位表示（在ARP标头中使用）
    const uint32_t next_hop_ip = next_hop.ipv4_numeric();

    // 查找ARP表中是否有下一跳的IP地址
    const auto& iter = _arp_table.find(next_hop_ip);
    if (iter == _arp_table.end()) {// 如果ARP表中没有下一跳的IP地址,则发送ARP请求
        //  IP等待表中没有下一跳的IP地址
        if(_ip_wait_time_table.find(next_hop_ip) == _ip_wait_time_table.end()){
            // 将ARP请求封装成以太网帧
            ARPMessage arp_message;
            arp_message.opcode = ARPMessage::OPCODE_REQUEST;
            arp_message.sender_ethernet_address = _ethernet_address;
            arp_message.sender_ip_address = _ip_address.ipv4_numeric();//本机ip
            arp_message.target_ethernet_address = {};
            arp_message.target_ip_address = next_hop_ip;//目标ip

            EthernetFrame frame;
            frame.header().src = _ethernet_address;
            frame.header().dst = ETHERNET_BROADCAST;// 广播寻址
            frame.header().type = EthernetHeader::TYPE_ARP;
            frame.payload() = arp_message.serialize();
            _frames_out.push(frame);

            _ip_wait_time_table[next_hop_ip] = WAIT_TIMEOUT;
        }
        //  将数据报文存入等待表，等待ARP响应后再发送
        //  同一个IP地址可能有多个数据报文等待发送
        _ip_dgram_wait_table[next_hop_ip].push_back(dgram);
    }else{
        // 如果ARP表中有下一跳的IP地址，则将数据报文封装成以太网帧
        EthernetFrame frame;
        frame.header().src = _ethernet_address;
        frame.header().dst = iter->second.eth_addr;//从arp表中查询到了下一跳的以太网地址
        frame.header().type = EthernetHeader::TYPE_IPv4;
        frame.payload() = dgram.serialize();
        _frames_out.push(frame);
    }
    
}

//! \param[in] frame the incoming Ethernet frame
optional<InternetDatagram> NetworkInterface::recv_frame(const EthernetFrame &frame) {
    // 如果目的地址不是本机的以太网地址或广播地址，则返回空
    if(frame.header().dst != _ethernet_address && frame.header().dst != ETHERNET_BROADCAST)
        return nullopt;
    
    if(frame.header().type == EthernetHeader::TYPE_IPv4){
        // 如果以太网帧的类型是IPv4，则返回数据报文
        InternetDatagram dgram;
        if(dgram.parse(frame.payload())!=ParseResult::NoError)
            return nullopt;
        else
            return dgram;
    } else if (frame.header().type==EthernetHeader::TYPE_ARP){
        // 如果以太网帧的类型是ARP，则处理ARP请求或回复
        ARPMessage arp_message;
        if(arp_message.parse(frame.payload())!=ParseResult::NoError)
            return nullopt;

        const auto& src_ip = arp_message.sender_ip_address;
        const auto& src_eth = arp_message.sender_ethernet_address;
        const auto& dst_ip = arp_message.target_ip_address;
        const auto& dst_eth = arp_message.target_ethernet_address;

        // 如果ARP请求的目标IP地址是本机的IP地址，则回复ARP请求
        bool is_request = arp_message.opcode == ARPMessage::OPCODE_REQUEST&&dst_ip == _ip_address.ipv4_numeric();
        if(is_request){
            ARPMessage reply;
            reply.opcode = ARPMessage::OPCODE_REPLY;
            reply.sender_ethernet_address = _ethernet_address;
            reply.sender_ip_address = _ip_address.ipv4_numeric();
            reply.target_ethernet_address = src_eth;
            reply.target_ip_address = src_ip;
            
            EthernetFrame reply_frame;
            reply_frame.header().src = _ethernet_address;
            reply_frame.header().dst = src_eth;
            reply_frame.header().type = EthernetHeader::TYPE_ARP;
            reply_frame.payload() = reply.serialize();
            _frames_out.push(reply_frame);
        }

        // 如果ARP是来自dst的响应，以太网地址是本机的以太网地址，则更新ARP表
        // 当然,如果是ARP请求,也要更新ARP表
        bool is_reply = arp_message.opcode == ARPMessage::OPCODE_REPLY&&dst_eth == _ethernet_address;
        if(is_reply||is_request){
            //  更新ARP表
            _arp_table[src_ip] = {src_eth, ARP_TIMEOUT};
            //  如果ARP表中有等待的数据报文，则发送
            const auto& iter = _ip_dgram_wait_table.find(src_ip);
            if(iter != _ip_dgram_wait_table.end()){
                for(const auto& dgram : iter->second){
                    EthernetFrame new_frame;
                    new_frame.header().src = _ethernet_address;
                    new_frame.header().dst = src_eth;
                    new_frame.header().type = EthernetHeader::TYPE_IPv4;
                    new_frame.payload() = dgram.serialize();
                    _frames_out.push(new_frame);
                }
                _ip_dgram_wait_table.erase(iter);
            }
            _ip_wait_time_table.erase(src_ip);//删除IP等待表中的IP地址
        }
    }
    return nullopt;
}

//! \param[in] ms_since_last_tick the number of milliseconds since the last call to this method
void NetworkInterface::tick(const size_t ms_since_last_tick) {

    // 将 ARP 表中过期的条目删除
    for (auto iter = _arp_table.begin(); iter != _arp_table.end(); /* nop */) {
        if (iter->second.ttl <= ms_since_last_tick)
            iter = _arp_table.erase(iter);
        else {
            iter->second.ttl -= ms_since_last_tick;
            ++iter;
        }
    }

    // 更新IP等待表中的时间
    for (auto iter = _ip_wait_time_table.begin(); iter != _ip_wait_time_table.end(); /* nop */) {
        // 如果 ARP 等待队列中的 ARP 请求过期
        if (iter->second <= ms_since_last_tick) {
            // 重新发送 ARP 请求
            ARPMessage arp_request;
            arp_request.opcode = ARPMessage::OPCODE_REQUEST;
            arp_request.sender_ethernet_address = _ethernet_address;
            arp_request.sender_ip_address = _ip_address.ipv4_numeric();
            arp_request.target_ip_address = iter->first;

            EthernetFrame frame;
            frame.header().dst = ETHERNET_BROADCAST;
            frame.header().src = _ethernet_address;
            frame.header().type = EthernetHeader::TYPE_ARP;
            frame.payload() = arp_request.serialize();
            _frames_out.push(frame);

            iter->second = WAIT_TIMEOUT;
        } else {
            iter->second -= ms_since_last_tick;
            ++iter;
        }
    }

}