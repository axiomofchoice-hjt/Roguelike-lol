#pragma once

#include "vec2.h"

namespace geo {
/// 二维线段
struct segment2d {
    /// 线段的一个端点
    vec2 p1;
    /// 线段的另一个端点
    vec2 p2;
    segment2d(vec2 v1, vec2 v2);
};

/// 线段移动
inline segment2d move(segment2d s, vec2 v) {
    return segment2d(s.p1 + v, s.p2 + v);
}

/// 判定两个线段相交
bool is_intersect(segment2d s1, segment2d s2);

/// 点到线段的距离
float distance(segment2d s, vec2 v);
}  // namespace geo