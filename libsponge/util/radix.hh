/*
 * Copyright (C) 2014-2024 Firejail Authors
 *
 * This file is part of firejail project
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
#ifndef RADIX_H
#define RADIX_H

#include <optional>
#include <vector>
#include <memory>
#include "util.hh"
#include "address.hh"


#define MASK32 0xFFFFFFFF

std::string mask_to_string(uint32_t ip, uint8_t length);
struct RouterEntry {
    uint32_t route_prefix;
    uint8_t prefix_length;
    std::optional<Address> next_hop;
    size_t interface_num;
};

class rnode_t {
public:
    bool has_value = false;
    RouterEntry value{};
    std::string str = "";
    std::vector<std::unique_ptr<rnode_t>> children{};
};

class RadixTree {
public:
    const RouterEntry& search(const std::string& str);
    void insert(const uint32_t route_prefix,
                   const uint8_t prefix_length,
                   const std::optional<Address> next_hop,
                   const size_t interface_num);
    std::unique_ptr<rnode_t> root = std::make_unique<rnode_t>();
    RouterEntry default_item{};
};

#endif