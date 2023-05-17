#pragma once

#include <fmt/core.h>
namespace geo {
/// 三维向量
struct vec3 {
    /// x 分量
    float x;
    /// y 分量
    float y;
    /// z 分量
    float z;
    vec3();
    vec3(float x, float y, float z);
};

inline vec3 operator+(vec3 v1, vec3 v2) {
    return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
inline vec3 operator-(vec3 v1, vec3 v2) {
    return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
inline vec3 operator*(vec3 v, float k) {
    return vec3(v.x * k, v.y * k, v.z * k);
}
inline vec3 operator*(float k, vec3 v) {
    return vec3(v.x * k, v.y * k, v.z * k);
}
inline vec3 operator/(vec3 v, float k) {
    return vec3(v.x / k, v.y / k, v.z / k);
}
inline vec3 &operator+=(vec3 &v1, vec3 v2) { return v1 = v1 + v2; }
inline vec3 &operator-=(vec3 &v1, vec3 v2) { return v1 = v1 - v2; }
inline vec3 &operator*=(vec3 &v, float k) { return v = v * k; }
inline vec3 &operator/=(vec3 &v, float k) { return v = v / k; }

/// 点积 / 内积 / 数量积
float dot(vec3 v1, vec3 v2);
/// 叉积 / 外积 / 向量积
vec3 cross(vec3 v1, vec3 v2);
/// 长度
float length(vec3 v);
/// 长度平方
float squared(vec3 v);
/// 两点的距离
float distance(vec3 v1, vec3 v2);
/// 单位向量
vec3 normalize(vec3 v);
/// 正交向量
vec3 orthogonal(vec3 v);
}  // namespace geo

/// fmt::formatter
template <>
struct fmt::formatter<geo::vec3> : formatter<float> {
    template <typename FormatContext>
    auto format(const geo::vec3 &p, FormatContext &ctx) const
        -> decltype(ctx.out()) {
        *ctx.out() = '(';
        formatter<float>::format(p.x, ctx);
        *ctx.out() = ',';
        *ctx.out() = ' ';
        formatter<float>::format(p.y, ctx);
        *ctx.out() = ',';
        *ctx.out() = ' ';
        formatter<float>::format(p.z, ctx);
        *ctx.out() = ')';
        return ctx.out();
    }
};