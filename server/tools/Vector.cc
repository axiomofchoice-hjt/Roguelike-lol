#include "Vector.h"

namespace Vector {
Vector2Proto to_proto(vec2 v) {
    Vector2Proto proto;
    proto.set_x(v.x);
    proto.set_y(v.y);
    return proto;
}

vec2 from_proto(const Vector2Proto &proto) {
    return vec2(proto.x(), proto.y());
}

Vector3Proto to_proto(vec3 v) {
    Vector3Proto proto;
    proto.set_x(v.x);
    proto.set_y(v.y);
    proto.set_z(v.z);
    return proto;
}

vec3 from_proto(const Vector3Proto &proto) {
    return vec3(proto.x(), proto.y(), proto.z());
}

vec2 vec3_to_vec2(vec3 v) { return vec2(v.x, v.z); }
}  // namespace Vector
