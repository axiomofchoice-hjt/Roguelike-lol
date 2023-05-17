#pragma once

#include <algorithm>
#include <cmath>

#include "geo/geo.h"
#include "proto/Scene.pb.h"

using geo::vec2;
using geo::vec3;

namespace Vector {
Vector2Proto to_proto(vec2 v);
vec2 from_proto(const Vector2Proto &proto);

Vector3Proto to_proto(vec3 v);
vec3 from_proto(const Vector3Proto &proto);

vec2 vec3_to_vec2(vec3 v);
}  // namespace Vector