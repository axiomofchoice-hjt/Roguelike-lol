#include "segment1d.h"
#include "test_tools.h"

TEST(segment1d, constructor) {
    geo::segment1d s(114, 514);
    test_eq(s.l, 114.f);
    test_eq(s.r, 514.f);
    s = geo::segment1d(514, 114);
    test_eq(s.l, 114.f);
    test_eq(s.r, 514.f);
}

TEST(segment1d, move) {
    auto t = move(geo::segment1d(1, 2), 3);
    test_eq(t, geo::segment1d(4, 5));
}

TEST(segment1d, is_contain) {
    test_eq(geo::is_contain(geo::segment1d(1, 2), 1), true);
    test_eq(geo::is_contain(geo::segment1d(1, 2), 2), true);
    test_eq(geo::is_contain(geo::segment1d(1, 2), 2.5), false);
    test_eq(geo::is_contain(geo::segment1d(1, 2), 0.5), false);
}

TEST(segment1d, is_intersect) {
    test_eq(geo::is_intersect(geo::segment1d(1, 2), geo::segment1d(2, 3)),
            true);
    test_eq(geo::is_intersect(geo::segment1d(1, 2), geo::segment1d(0, 1)),
            true);
    test_eq(geo::is_intersect(geo::segment1d(1, 2), geo::segment1d(2.5, 3)),
            false);
    test_eq(geo::is_intersect(geo::segment1d(1, 2), geo::segment1d(0, 0.5)),
            false);
}