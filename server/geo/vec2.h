#pragma once

#include <fmt/core.h>

namespace geo {
/// 二维向量
struct vec2 {
    /// x 分量
    float x;
    /// y 分量
    float y;
    vec2();
    vec2(float x, float y);
};

inline vec2 operator+(vec2 v1, vec2 v2) {
    return vec2(v1.x + v2.x, v1.y + v2.y);
}
inline vec2 operator-(vec2 v1, vec2 v2) {
    return vec2(v1.x - v2.x, v1.y - v2.y);
}
inline vec2 operator*(vec2 v1, float k) { return vec2(v1.x * k, v1.y * k); }
inline vec2 operator*(float k, vec2 v1) { return vec2(v1.x * k, v1.y * k); }
inline vec2 operator/(vec2 v1, float k) { return vec2(v1.x / k, v1.y / k); }
inline vec2 &operator+=(vec2 &v1, vec2 v2) { return v1 = v1 + v2; }
inline vec2 &operator-=(vec2 &v1, vec2 v2) { return v1 = v1 - v2; }
inline vec2 &operator*=(vec2 &v, float k) { return v = v * k; }
inline vec2 &operator/=(vec2 &v, float k) { return v = v / k; }
/// 点积 / 内积 / 数量积
float dot(vec2 v1, vec2 v2);
/// 叉积 / 外积 / 向量积（在 z 轴的分量）
float cross(vec2 v1, vec2 v2);
/// 长度
float length(vec2 v);
/// 长度平方
float squared(vec2 v);
/// 两点的距离
float distance(vec2 v1, vec2 v2);
/// 单位向量
vec2 normalize(vec2 v);
}  // namespace geo

/// fmt::formatter
template <>
struct fmt::formatter<geo::vec2> : formatter<float> {
    template <typename FormatContext>
    auto format(const geo::vec2 &p, FormatContext &ctx) const
        -> decltype(ctx.out()) {
        *ctx.out() = '(';
        formatter<float>::format(p.x, ctx);
        *ctx.out() = ',';
        *ctx.out() = ' ';
        formatter<float>::format(p.y, ctx);
        *ctx.out() = ')';
        return ctx.out();
    }
};