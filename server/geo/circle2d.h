#pragma once

#include <utility>

#include "line2d.h"
#include "segment2d.h"
#include "vec2.h"

namespace geo {
/// 圆
struct circle2d {
    /// 圆心
    vec2 o;
    /// 半径
    float r;
    circle2d(vec2 o, float radius);
};

/// 判定点在圆内
bool is_contain(circle2d c, vec2 p);
/// 判定线段在圆外
bool is_out(circle2d c, segment2d s);
/// 圆与直线的交点
std::pair<vec2, vec2> intersection(circle2d c, line2d l);
/// 两圆的交点
std::pair<vec2, vec2> intersection(circle2d c1, circle2d c2);
}  // namespace geo