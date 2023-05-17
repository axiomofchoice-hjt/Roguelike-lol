#pragma once
#include <gtest/gtest.h>

#include <cmath>

#include "segment1d.h"
#include "segment2d.h"
#include "vec2.h"
#include "vec3.h"

constexpr float eps = 0.00001f;

using geo::vec2;
using geo::vec3;

template <typename T>
inline bool equal(T a, T b) {
    return a == b;
}
inline bool equal(float a, float b) { return std::abs(a - b) <= eps; }
inline bool equal(vec2 a, vec2 b) { return equal(a.x, b.x) && equal(a.y, b.y); }
inline bool equal(vec3 a, vec3 b) {
    return equal(a.x, b.x) && equal(a.y, b.y) && equal(a.z, b.z);
}
inline bool equal(geo::segment1d a, geo::segment1d b) {
    return equal(a.l, b.l) && equal(a.r, b.r);
}
inline bool equal(geo::segment2d a, geo::segment2d b) {
    return (equal(a.p1, b.p1) && equal(a.p2, b.p2)) ||
           (equal(a.p1, b.p2) && equal(a.p2, b.p1));
}

template <typename T>
void test_eq(T a, T b) {
    EXPECT_TRUE(equal(a, b));
}