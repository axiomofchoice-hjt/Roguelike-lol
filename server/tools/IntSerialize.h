#pragma once

#include <string>

#include "tools/basic.h"

namespace IntSerialize {
inline u64 getSize(const std::string &s) {
    return (u64)s[0] | ((u64)s[1] << 8) | ((u64)s[2] << 16) | ((u64)s[3] << 24);
}

inline bool completed(const std::string &s) {
    return s.length() >= 4 && getSize(s) + 4 <= s.length();
}

inline std::string popFront(std::string &s) {
    size_t sz = getSize(s);
    std::string ret(s.begin() + 4, s.begin() + 4 + sz);
    s.erase(s.begin(), s.begin() + 4 + sz);
    return ret;
}

inline void putSize(std::string &s) {
    size_t sz = s.length();
    s.insert(s.begin(), 4, 0);
    s[0] = (uint8_t)(sz & 0xff);
    s[1] = (uint8_t)((sz >> 8) & 0xff);
    s[2] = (uint8_t)((sz >> 16) & 0xff);
    s[3] = (uint8_t)((sz >> 24) & 0xff);
}
}  // namespace IntSerialize