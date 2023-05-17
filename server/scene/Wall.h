#pragma once

#include "geo/segment2d.h"
#include "proto/Scene.pb.h"
#include "tools/Vector.h"
#include "tools/basic.h"

class Entity;
class Scene;

/// 墙
namespace wall {
constexpr float Length = 3.f;
constexpr float Thickness = 0.3f;

class Wall {
   public:
    u64 id;
    vec2 p1;
    vec2 p2;
    float height;
    bool activate;
    Wall(vec2 a, vec2 b);
    /// 将实体排开
    void collide(Entity &entity) const;
    /// 路径是否撞墙
    bool is_intersect(geo::segment2d segment, float collide_radius) const;
    /// 位置是否撞墙
    bool is_intersect(geo::vec2 point, float collide_radius) const;

    void update(const float deltaTime, Scene *scene);

    WallProto proto() const;

    void print() const;
};

/// 放置一个 AABB 矩形的墙
void add_rect(Scene *scene, vec2 a, vec2 b);
}  // namespace wall