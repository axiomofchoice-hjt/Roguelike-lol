#include "vec2.h"

#include <cmath>

namespace geo {
vec2::vec2() : x(0.f), y(0.f){};
vec2::vec2(float x, float y) : x(x), y(y) {}

float dot(vec2 v1, vec2 v2) { return v1.x * v2.x + v1.y * v2.y; }
float cross(vec2 v1, vec2 v2) { return v1.x * v2.y - v1.y * v2.x; }
float length(vec2 v) { return std::hypot(v.x, v.y); }
float squared(vec2 v) { return dot(v, v); }
float distance(vec2 v1, vec2 v2) { return length(v1 - v2); }
vec2 normalize(vec2 v) { return v * (1 / length(v)); }
}  // namespace geo