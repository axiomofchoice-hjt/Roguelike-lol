#include "circle2d.h"
#include "test_tools.h"

TEST(circle2d, constructor) {
    geo::circle2d c(vec2(1, 2), 3.f);
    test_eq(c.o, vec2(1, 2));
    test_eq(c.r, 3.f);
}