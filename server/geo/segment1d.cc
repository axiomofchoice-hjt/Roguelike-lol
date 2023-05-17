#include "segment1d.h"

#include <algorithm>
#include <type_traits>

namespace geo {
segment1d::segment1d(float p1, float p2) : l(p1), r(p2) {
    if (l > r) {
        std::swap(l, r);
    }
}

bool is_contain(segment1d s, float f) { return s.l <= f && f <= s.r; }

bool is_intersect(segment1d s1, segment1d s2) {
    return !(s1.r < s2.l || s2.r < s1.l);
}
}  // namespace geo