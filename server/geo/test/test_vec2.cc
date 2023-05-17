#include "test_tools.h"
#include "vec2.h"

TEST(vec2, default_constructor) {
    vec2 a;
    test_eq(a.x, 0.f);
    test_eq(a.y, 0.f);
}

TEST(vec2, constructor) {
    vec2 a(114514, 1919810);
    test_eq(a.x, 114514.f);
    test_eq(a.y, 1919810.f);
}

TEST(vec2, add) {
    vec2 a = vec2(1, 2) + vec2(10, 20);
    test_eq(a, vec2(11, 22));
    a += vec2(100, 200);
    test_eq(a, vec2(111, 222));
}

TEST(vec2, sub) {
    vec2 a = vec2(1, 2) - vec2(10, 20);
    test_eq(a, vec2(-9, -18));
    a -= vec2(100, 200);
    test_eq(a, vec2(-109, -218));
}

TEST(vec2, mul) {
    vec2 a = vec2(1, 2) * 10;
    test_eq(a, vec2(10, 20));
    a = 10 * vec2(1, 2);
    test_eq(a, vec2(10, 20));
    a *= 20;
    test_eq(a, vec2(200, 400));
}

TEST(vec2, div) {
    vec2 a = vec2(1, 2) / 8;
    test_eq(a, vec2(0.125, 0.25));
    a /= 2;
    test_eq(a, vec2(0.0625, 0.125));
}

TEST(vec2, dot) {
    float a = geo::dot(vec2(3, 4), vec2(50, 60));
    test_eq(a, 150.f + 240.f);
}

TEST(vec2, cross) {
    float a = geo::cross(vec2(3, 4), vec2(50, 60));
    test_eq(a, 180.f - 200.f);
}

TEST(vec2, length) {
    float a = geo::length(vec2(3, 4));
    test_eq(a, 5.f);
}

TEST(vec2, squared) {
    float a = geo::squared(vec2(3, 4));
    test_eq(a, 25.f);
}

TEST(vec2, distance) {
    float a = geo::distance(vec2(3, 4), vec2(7, 7));
    test_eq(a, 5.f);
}

TEST(vec2, normalize) {
    vec2 a = geo::normalize(vec2(3, 4));
    test_eq(a, vec2(0.6f, 0.8f));
}

TEST(vec2, fmt) {
    test_eq(fmt::format("{:.1f}", vec2(1.2, 3.4)), std::string("(1.2, 3.4)"));
}