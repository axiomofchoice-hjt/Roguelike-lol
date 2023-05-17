#include "line2d.h"

#include <cmath>

#include "vec2.h"

namespace geo {
line2d::line2d(vec2 v1, vec2 v2) : p1(v1), p2(v2) {}

line2d_general::line2d_general(float a, float b, float c) : a(a), b(b), c(c) {}

line2d_general to_line2d_general(line2d l) {
    return line2d_general(l.p1.y - l.p2.y, l.p2.x - l.p1.x,
                          l.p1.x * l.p2.y - l.p2.x * l.p1.y);
}

line2d to_line2d(line2d_general l) {
    if (l.a == 0) {
        return line2d(vec2(0, -l.c / l.b), vec2(1, -l.c / l.b));
    } else {
        return line2d(vec2(-l.c / l.a, 0), vec2(-(l.c + l.b) / l.a, 1));
    }
}

float distance(line2d l, vec2 v) {
    return std::abs(cross(l.p2 - l.p1, v - l.p1)) / length(l.p2 - l.p1);
}

vec2 closest_point(line2d l, vec2 v) {
    vec2 d = l.p2 - l.p1;
    return l.p1 + d * (dot(v - l.p1, d) / squared(d));
}

vec2 intersection(line2d l1, line2d l2) {
    float t1 = cross(l1.p1 - l2.p1, l2.p2 - l2.p1);
    float t2 = cross(l1.p2 - l2.p1, l2.p2 - l2.p1);
    return (l1.p2 * t1 - l1.p1 * t2) * (1 / (t1 - t2));
}
}  // namespace geo