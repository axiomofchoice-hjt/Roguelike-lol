#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>
#include <random>

#include "proto/Scene.pb.h"
#include "tools/log.h"

// types

using u64 = uint64_t;
using u32 = uint32_t;

template <typename T>
using uptr = std::unique_ptr<T>;

template <typename T>
using shared = std::shared_ptr<T>;

template <typename T>
using weak = std::weak_ptr<T>;

namespace Rand {
/// mt19937 对象
extern std::mt19937_64 gen;

/// 随机整数 [0, mod - 1]
int d(int mod);
/// 随机浮点数 [0, 1)
float f();
/// 随机浮点数 [l, r)
float f(float l, float r);
};  // namespace Rand

constexpr float PI = 3.14159265358979f;

struct LimitValue {
    float now;
    float max;
    LimitValue() : now(), max() {}
    LimitValue(float now, float max) : now(now), max(max) {}
    void add(float v) {
        now += v;
        now = std::max(now, 0.f);
        now = std::min(now, max);
    }
    LimitValueProto proto() const {
        LimitValueProto res;
        res.set_now(now);
        res.set_max(max);
        return res;
    }
};

template <typename T>
class SmallSet {
   private:
    std::vector<T> data;

   public:
    SmallSet() : data() { data.reserve(std::max(1ul, 64 / sizeof(T))); }
    void insert(T x) { data.push_back(x); }
    void erase(T x) {
        for (auto it = data.begin(); it < data.end(); ++it) {
            if (*it == x) {
                data.erase(it);
                break;
            }
        }
    }
    bool contains(T x) const {
        for (auto &i : data) {
            if (i == x) {
                return true;
            }
        }
        return false;
    }
};