#include <cmath>

namespace geo {
inline float squared(float x) { return x * x; }
inline float distance(float x, float y) { return std::abs(x - y); }
}  // namespace geo