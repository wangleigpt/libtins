/*
 * Copyright (c) 2017, Matias Fontanini
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "memory_helpers.h"
#include "ip_address.h"
#include "ipv6_address.h"
#include "hw_address.h"

using std::vector;

namespace Tins {
namespace Memory {

// InputMemoryStream

void InputMemoryStream::read(vector<uint8_t>& value, size_t count) {
    if (!can_read(count)) {
        throw malformed_packet();
    }
    value.assign(pointer(), pointer() + count);
    skip(count);
}

void InputMemoryStream::read(HWAddress<6>& address) {
    if (!can_read(address.size())) {
        throw malformed_packet();
    }
    address = pointer();
    skip(address.size());
}

void InputMemoryStream::read(IPv4Address& address) {
    address = IPv4Address(read<uint32_t>());
}

void InputMemoryStream::read(IPv6Address& address) {
    if (!can_read(IPv6Address::address_size)) {
        throw malformed_packet();
    }
    address = pointer();
    skip(IPv6Address::address_size);
}

// OutputMemoryStream

void OutputMemoryStream::write(const HWAddress<6>& address) {
    write(address.begin(), address.end());
}

void OutputMemoryStream::write(const IPv4Address& address) {
    write(static_cast<uint32_t>(address));
}

void OutputMemoryStream::write(const IPv6Address& address) {
    write(address.begin(), address.end());
}

} // Memory
} // Tins
