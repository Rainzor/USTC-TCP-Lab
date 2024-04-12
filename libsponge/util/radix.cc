#include "radix.hh"

#include <iostream>

using namespace std;
std::string mask_to_string(uint32_t ip, uint8_t length)
{
    std::string binaryString;

    for (uint8_t i = 0; i < length; ++i) {
        uint8_t bit = (ip >> (31 - i)) & 1;
        binaryString += std::to_string(bit);
    }
    return binaryString;
}
const RouterEntry& RadixTree::search(const std::string& str){
    rnode_t* node = root.get();
    size_t index = 0;
    std::string _path = str;
    rnode_t* chosen = nullptr;

    while (index < node->children.size()) {
        rnode_t* child = node->children[index].get();
        if (child->str == _path) {
            return child->value;
        }
        if (child->str.length() < _path.length() && 
            node->children[index].get()->str == _path.substr(0, child->str.length())) {
            node = child;
            _path = _path.substr(child->str.length());
            chosen = child;
            index = 0;
            continue;
        }
        else{
            index++;
        }
    }
	if(chosen != nullptr && chosen->has_value) 
        return chosen->value;
    return default_item;
}


void RadixTree::insert(const uint32_t route_prefix,
                   const uint8_t prefix_length,
                   const std::optional<Address> next_hop,
                   const size_t interface_num)
{   
    RouterEntry value = {route_prefix, prefix_length, next_hop, interface_num};
    string str = mask_to_string(route_prefix, prefix_length);
    if (str.empty()) {
        default_item = value;
        return;
    }

    rnode_t* node = root.get();
    size_t index = 0;
    std::string common_prefix = "";
    rnode_t* common_prefix_node = root.get();
    string _path = str;

    while (index < node->children.size()) {
        common_prefix_node = node;
        rnode_t* child = node->children[index].get();
        if (child->str == _path) {
            common_prefix = _path;
            common_prefix_node = child;
            break;
        }
        if (child->str.length() < _path.length() && _path.substr(0, child->str.length()) == child->str) {
        	_path = _path.substr(child->str.length());
            common_prefix += child->str;
            node = child;
            index = 0;
            continue;
        }
        else {
            index++;
        }
    }

    if (common_prefix == str) {
        common_prefix_node->has_value = true;
        common_prefix_node->value = value;
        return;
    }

    std::string remaining = str.substr(common_prefix.length());

    for (size_t idx = 0; idx < common_prefix_node->children.size(); idx++) {
        rnode_t* child = common_prefix_node->children[idx].get();
        if (child->str[0] == remaining[0]) {
            size_t i = 0;
            while (i < child->str.length() && i < remaining.length() && child->str[i] == remaining[i]) {
                i++;
            }

            auto new_child = std::make_unique<rnode_t>();
            new_child->str = child->str.substr(0,i);
            auto grandson1 = std::make_unique<rnode_t>();
            grandson1->str = child->str.substr(i);
            grandson1->has_value = child->has_value;
            grandson1->value = child->value;
            grandson1->children = std::move(child->children);

			auto grandson2 = std::make_unique<rnode_t>();
            grandson2->str = remaining.substr(i);
            grandson2->has_value = true;
            grandson2->value = value;

            new_child->children.push_back(std::move(grandson1));
            new_child->children.push_back(std::move(grandson2));
            common_prefix_node->children[idx] = std::move(new_child);
            return;
        }
    }
    auto new_node = std::make_unique<rnode_t>();
    new_node->str = remaining;
    new_node->has_value = true;
    new_node->value = value;
    common_prefix_node->children.push_back(std::move(new_node));
}