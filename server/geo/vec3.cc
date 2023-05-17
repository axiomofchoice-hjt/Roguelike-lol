#include "vec3.h"

#include <cmath>

namespace geo {
vec3::vec3() : x(), y(), z() {}
vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) {}

float dot(vec3 v1, vec3 v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
vec3 cross(vec3 v1, vec3 v2) {
    return vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x);
}
float length(vec3 v) { return std::sqrt(dot(v, v)); }
float squared(vec3 v) { return dot(v, v); }
float distance(vec3 v1, vec3 v2) { return length(v1 - v2); }
vec3 normalize(vec3 v) { return v * (1 / length(v)); }
vec3 orthogonal(vec3 v) {
    if (v.x == 0) {
        return vec3(1, 0, 0);
    } else {
        return geo::cross(v, vec3(0, 1, 1));
    }
}
}  // namespace geo