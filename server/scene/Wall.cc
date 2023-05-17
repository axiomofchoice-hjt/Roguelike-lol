#include "Wall.h"

#include <algorithm>

#include "geo/vec2.h"
#include "proto/Scene.pb.h"
#include "scene/Config.h"
#include "scene/Entity.h"
#include "scene/Scene.h"
#include "tools/UUID.h"
#include "tools/log.h"

namespace wall {
Wall::Wall(vec2 a, vec2 b) : p1(a), p2(b) {
    activate = false;
    if (p1.x != p2.x && p1.y != p2.y) {
        log_error("wall::add_line error");
        return;
    }
    if (p1.y > p2.y) {
        std::swap(p1.y, p2.y);
    }
    if (p1.x > p2.x) {
        std::swap(p1.x, p2.x);
    }
    id = UUID::get();
    height = 0;
    // if (p1.x == p2.x) {
    //     for (float i = p1.y + Length / 2; i < p2.y; i += Length) {
    //         auto t = scene->addEntity(UUID::get(),
    //         EntityProto_EntityType_Wall); *t->position = vec2(p1.x, i);
    //         t->scale = vec3(Thickness, Length, Length);
    //     }
    // } else if (p1.y == p2.y) {
    //     for (float i = p1.x + Length / 2; i < p2.x; i += Length) {
    //         auto t = scene->addEntity(UUID::get(),
    //         EntityProto_EntityType_Wall); *t->position = vec2(i, p1.y);
    //         t->scale = vec3(Length, Length, Thickness);
    //     }
    // }
}

void add_rect(Scene *scene, vec2 a, vec2 b) {
    scene->walls.push_back(
        std::make_shared<Wall>(vec2(a.x, a.y), vec2(a.x, b.y)));
    scene->walls.push_back(
        std::make_shared<Wall>(vec2(a.x, b.y), vec2(b.x, b.y)));
    scene->walls.push_back(
        std::make_shared<Wall>(vec2(b.x, b.y), vec2(b.x, a.y)));
    scene->walls.push_back(
        std::make_shared<Wall>(vec2(b.x, a.y), vec2(a.x, a.y)));
}

void Wall::collide(Entity &entity) const {
    const float radius = entity.collide_radius;
    vec2 &pos = *entity.position;
    bool flag = true;

    if (p1.x == p2.x) {
        if (p1.x - radius < pos.x && pos.x < p1.x + radius && p1.y <= pos.y &&
            pos.y <= p2.y) {
            if (pos.x < p1.x) {
                pos.x = p1.x - radius;
            } else {
                pos.x = p1.x + radius;
            }
        } else if (geo::distance(*entity.position, p1) < radius) {
            pos = p1 + geo::normalize(pos - p1) * radius;
        } else if (geo::distance(*entity.position, p2) < radius) {
            pos = p2 + geo::normalize(pos - p2) * radius;
        } else {
            flag = false;
        }
    } else {
        if (p1.y - radius < pos.y && pos.y < p1.y + radius && p1.x <= pos.x &&
            pos.x <= p2.x) {
            if (pos.y < p1.y) {
                pos.y = p1.y - radius;
            } else {
                pos.y = p1.y + radius;
            }
        } else if (geo::distance(*entity.position, p1) < radius) {
            pos = p1 + geo::normalize(pos - p1) * radius;
        } else if (geo::distance(*entity.position, p2) < radius) {
            pos = p2 + geo::normalize(pos - p2) * radius;
        } else {
            flag = false;
        }
    }
    if (flag) {
        entity.move_to = nullptr;
    }
}

bool Wall::is_intersect(geo::segment2d segment, float collide_radius) const {
    if (!geo::is_out(geo::circle2d(p1, collide_radius), segment)) {
        return true;
    }
    if (!geo::is_out(geo::circle2d(p2, collide_radius), segment)) {
        return true;
    }
    if (p1.x == p2.x) {
        if (geo::is_intersect(
                geo::move(geo::segment2d(p1, p2), vec2(collide_radius, 0)),
                segment)) {
            return true;
        }
        if (geo::is_intersect(
                geo::move(geo::segment2d(p1, p2), vec2(-collide_radius, 0)),
                segment)) {
            return true;
        }
    } else {
        if (geo::is_intersect(
                geo::move(geo::segment2d(p1, p2), vec2(0, collide_radius)),
                segment)) {
            return true;
        }
        if (geo::is_intersect(
                geo::move(geo::segment2d(p1, p2), vec2(0, -collide_radius)),
                segment)) {
            return true;
        }
    }
    return false;
}

bool Wall::is_intersect(geo::vec2 point, float collide_radius) const {
    return geo::distance(geo::segment2d(p1, p2), point) <= collide_radius;
}

WallProto Wall::proto() const {
    WallProto proto;
    proto.set_id(id);
    *proto.mutable_p1() = Vector::to_proto(p1);
    *proto.mutable_p2() = Vector::to_proto(p2);
    proto.set_height(height);
    return proto;
}

void Wall::update(const float deltaTime, Scene *scene) {
    if (activate) {
        if (height < 0) {
            height += deltaTime * Config::wall_speed();
            height = std::min(height, 0.f);
        }
        for (auto &i : scene->entities) {
            if ((i->type == EntityProto_EntityType_Player &&
                 i->action.type != EntityProto_ActionType_KaisaR) ||
                i->type == EntityProto_EntityType_Melee) {
                collide(*i);
            }
        }
    } else {
        if (height > -Length - 0.1f) {
            height -= deltaTime * Config::wall_speed();
            height = std::max(height, -Length - 0.1f);
        }
    }
}

void Wall::print() const {
    log_info("wall id={} p1=({}, {}) p2=({}, {}) height={}, activate={}", id,
             p1.x, p1.y, p2.x, p2.y, height, activate);
}
}  // namespace wall