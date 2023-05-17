#include <fmt/core.h>

#include <cmath>

#include "test_tools.h"
#include "vec3.h"

TEST(vec3, default_constructor) {
    vec3 a;
    test_eq(a.x, 0.f);
    test_eq(a.y, 0.f);
    test_eq(a.z, 0.f);
}

TEST(vec3, constructor) {
    vec3 a(11, 45, 14);
    test_eq(a.x, 11.f);
    test_eq(a.y, 45.f);
    test_eq(a.z, 14.f);
}

TEST(vec3, add) {
    vec3 a = vec3(1, 2, 3) + vec3(10, 20, 30);
    test_eq(a, vec3(11, 22, 33));
    a += vec3(100, 200, 300);
    test_eq(a, vec3(111, 222, 333));
}

TEST(vec3, sub) {
    vec3 a = vec3(1, 2, 3) - vec3(10, 20, 30);
    test_eq(a, vec3(-9, -18, -27));
    a -= vec3(100, 200, 300);
    test_eq(a, vec3(-109, -218, -327));
}

TEST(vec3, mul) {
    vec3 a = vec3(1, 2, 3) * 10;
    test_eq(a, vec3(10, 20, 30));
    a = 10 * vec3(1, 2, 3);
    test_eq(a, vec3(10, 20, 30));
    a *= 20;
    test_eq(a, vec3(200, 400, 600));
}

TEST(vec3, div) {
    vec3 a = vec3(1, 2, 3) / 8;
    test_eq(a, vec3(0.125, 0.25, 0.375));
    a /= 2;
    test_eq(a, vec3(0.0625, 0.125, 0.1875));
}

TEST(vec3, dot) {
    float a = geo::dot(vec3(3, 4, 5), vec3(50, 60, 70));
    test_eq(a, 150.f + 240.f + 350.f);
}

TEST(vec3, cross) {
    vec3 a = geo::cross(vec3(3, 4, 5), vec3(50, 60, 70));
    test_eq(a, vec3(-20, 40, -20));
}

TEST(vec3, length) {
    float a = geo::length(vec3(3, 4, 7));
    test_eq(a, std::sqrt(74.f));
}

TEST(vec3, squared) {
    float a = geo::squared(vec3(3, 4, 7));
    test_eq(a, 74.f);
}

TEST(vec3, distance) {
    float a = geo::distance(vec3(3, 4, 5), vec3(10, 20, 30));
    test_eq(a, std::sqrt(930.f));
}

TEST(vec3, normalize) {
    vec3 a = geo::normalize(vec3(1, 2, 2));
    test_eq(a, vec3(1, 2, 2) / 3);
}

TEST(vec3, orthogonal) {
    {
        vec3 a(1, 5, 7);
        vec3 orth = geo::orthogonal(a);
        test_eq(dot(orth, a), 0.f);
        test_eq(geo::length(orth) > eps, true);
    }
    {
        vec3 a(0, 5, 7);
        vec3 orth = geo::orthogonal(a);
        test_eq(dot(orth, a), 0.f);
        test_eq(geo::length(orth) > eps, true);
    }
}

TEST(vec3, fmt) {
    test_eq(fmt::format("{:.1f}", vec3(1.2, 3.4, 5.6)),
            std::string("(1.2, 3.4, 5.6)"));
}