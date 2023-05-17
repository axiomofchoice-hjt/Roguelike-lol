#include "line2d.h"
#include "test_tools.h"
#include "vec2.h"

TEST(line2d, constructor) {
    vec2 a(114514, 1919810);
    vec2 b(3, 4);
    geo::line2d l(a, b);
    test_eq(l.p1, vec2(114514.f, 1919810.f));
    test_eq(l.p2, vec2(3.f, 4.f));
}

TEST(line2d, distance) {
    {
        vec2 a(1, 2);
        vec2 b(2, 3);
        geo::line2d l(a, b);
        vec2 p(5, 1);
        test_eq(geo::distance(l, p), 2.5f * std::sqrt(2.f));
    }
    {
        vec2 a(1, 2);
        vec2 b(4, 5);
        geo::line2d l(a, b);
        vec2 p(5, 1);
        test_eq(geo::distance(l, p), 2.5f * std::sqrt(2.f));
    }
}

TEST(line2d, closest_point) {
    {
        vec2 a(1, 2);
        vec2 b(2, 3);
        geo::line2d l(a, b);
        vec2 p(5, 1);
        test_eq(geo::closest_point(l, p), vec2(2.5, 3.5));
    }
    {
        vec2 a(1, 2);
        vec2 b(4, 5);
        geo::line2d l(a, b);
        vec2 p(5, 1);
        test_eq(geo::closest_point(l, p), vec2(2.5, 3.5));
    }
}

TEST(line2d, intersection) {
    geo::line2d a(vec2(0, 1), vec2(2, 0));
    geo::line2d b(vec2(-1, 0), vec2(1, 1));
    test_eq(geo::intersection(a, b), vec2(0.5, 0.75));
}