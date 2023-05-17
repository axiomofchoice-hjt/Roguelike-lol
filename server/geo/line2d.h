#pragma once

#include "vec2.h"

namespace geo {
/// 二维直线 两点式
struct line2d {
    /// 直线上的一点
    vec2 p1;
    /// 直线上的另一点
    vec2 p2;
    line2d(vec2 v1, vec2 v2);
};

/// 二维直线 一般式 ax + by + c = 0
struct line2d_general {
    float a;
    float b;
    float c;
    line2d_general(float a, float b, float c);
};

/// 转换到一般式
line2d_general to_line2d_general(line2d l);
/// 转换到两点式
line2d to_line2d(line2d_general l);
/// 点到直线的距离
float distance(line2d l, vec2 v);
/// 垂足 / 直线上与指定点距离最近的点
vec2 closest_point(line2d l, vec2 v);
/// 两条直线的交点
vec2 intersection(line2d l1, line2d l2);
}  // namespace geo