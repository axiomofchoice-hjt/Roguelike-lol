#include "circle2d.h"

#include <cmath>
#include <utility>

#include "geo_float.h"
#include "line2d.h"
#include "segment2d.h"
#include "vec2.h"

namespace geo {
circle2d::circle2d(vec2 o, float radius) : o(o), r(radius) {}

bool is_contain(circle2d c, vec2 p) { return distance(c.o, p) <= c.r; }

bool is_out(circle2d c, segment2d s) { return distance(s, c.o) > c.r; }

std::pair<vec2, vec2> intersection(circle2d c, line2d l) {
    vec2 mid = closest_point(l, c.o);
    vec2 delta =
        normalize(l.p2 - l.p1) * std::sqrt(c.r * c.r - squared(c.o - mid));
    return std::make_pair(mid - delta, mid + delta);
}

std::pair<vec2, vec2> intersection(circle2d c1, circle2d c2) {
    float a = squared(c2.o - c1.o);
    float b =
        c1.r * (squared(c1.r) - squared(c2.r) + a) / (2 * c1.r * std::sqrt(a));
    float c = std::sqrt(c1.r * c1.r - b * b);
    vec2 k = normalize(c2.o - c1.o);
    vec2 mid = c1.o + k * b;
    vec2 delta = vec2(k.y, -k.x) * c;
    return {mid - delta, mid + delta};
}
}  // namespace geo