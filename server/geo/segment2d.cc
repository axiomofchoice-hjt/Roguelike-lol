#include "segment2d.h"

#include <algorithm>

#include "line2d.h"
#include "segment1d.h"
#include "vec2.h"

namespace geo {
segment2d::segment2d(vec2 v1, vec2 v2) : p1(v1), p2(v2) {}

/// 浮点数符号
static inline int sign(float f) { return f > 0 ? 1 : f < 0 ? -1 : 0; }

bool is_intersect(segment2d l1, segment2d l2) {
    return is_intersect(segment1d(l1.p1.x, l1.p2.x),
                        segment1d(l2.p1.x, l2.p2.x)) &&
           is_intersect(segment1d(l1.p1.y, l1.p2.y),
                        segment1d(l2.p1.y, l2.p2.y)) &&
           sign(cross(l2.p1 - l1.p1, l2.p2 - l1.p1)) *
                   sign(cross(l2.p1 - l1.p2, l2.p2 - l1.p2)) <=
               0 &&
           sign(cross(l1.p1 - l2.p1, l1.p2 - l2.p1)) *
                   sign(cross(l1.p1 - l2.p2, l1.p2 - l2.p2)) <=
               0;
}

float distance(segment2d s, vec2 v) {
    vec2 t = closest_point(line2d(s.p1, s.p2), v);
    if (is_contain(segment1d(s.p1.x, s.p2.x), v.x) &&
        is_contain(segment1d(s.p1.y, s.p2.y), v.y)) {
        return distance(t, v);
    } else {
        return std::min(distance(s.p1, v), distance(s.p2, v));
    }
}
}  // namespace geo