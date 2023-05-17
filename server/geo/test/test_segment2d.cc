#include <cmath>

#include "segment2d.h"
#include "test_tools.h"

TEST(segment2d, constructor) {
    test_eq(geo::segment2d(vec2(1, 2), vec2(3, 4)),
            geo::segment2d(vec2(3, 4), vec2(1, 2)));
    auto a = geo::segment2d(vec2(11, 45), vec2(1, 4));
    test_eq(a.p1, vec2(11, 45));
    test_eq(a.p2, vec2(1, 4));
}

TEST(segment2d, move) {
    test_eq(geo::move(geo::segment2d(vec2(1, 2), vec2(3, 4)), vec2(100, 200)),
            geo::segment2d(vec2(101, 202), vec2(103, 204)));
}

TEST(segment2d, is_intersect) {
    auto a = geo::segment2d(vec2(0, 0), vec2(1.5, 1.5));
    auto b = geo::segment2d(vec2(3, 0), vec2(0, 2));
    auto c = geo::segment2d(vec2(3, 0), vec2(0, 4));
    test_eq(geo::is_intersect(a, b), true);
    test_eq(geo::is_intersect(a, c), false);
}

TEST(segment2d, distance) {
    auto s = geo::segment2d(vec2(-1, 1), vec2(3, 3));
    test_eq(geo::distance(s, vec2(1, 1)), 2.f / std::sqrt(5.f));
    s = geo::segment2d(vec2(1, 2), vec2(3, 3));
    test_eq(geo::distance(s, vec2(1, 1)), 1.f);
}