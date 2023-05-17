#include "Entity.h"

#include "Wall.h"
#include "action/Attack.h"
#include "action/comb.h"
#include "scene/Config.h"
#include "scene/Scene.h"
#include "tools/basic.h"
#include "tools/log.h"

Entity::Entity(u64 id, EntityProto_EntityType type) : id(id), type(type) {
    action = action::comb::Idle();
    next_action = action::comb::Idle();
    move_to = nullptr;
    position = std::make_shared<vec2>();
    velocity = vec3();
    rotation = 0;
    collide_radius = 1.f;
    height = 0;
    removed = false;
    blood = LimitValue(100.f, 100.f);
    attack_hand = false;
    Acd = LimitValue(0, 100.f);
    Qcd = LimitValue(0, 100.f);
    Wcd = LimitValue(0, 100.f);
    Ecd = LimitValue(0, 100.f);
    Rcd = LimitValue(0, 100.f);

    if (type == EntityProto_EntityType_Satchel) {
        height = -wall::Length - 0.1f;
    }
    if (type == EntityProto_EntityType_Nexus) {
        height = -7 - 0.1f;
    }
}

Entity::~Entity() {}

void Entity::update(const float deltaTime, Scene *scene) {
    moving = false;
    velocity = vec3();
    if (Config::movable(*this) && move_to != nullptr) {
        float tmpDeltaTime = deltaTime;
        float speed = Config::speed(*this);
        if (!scene->map->working_room &&
            type == EntityProto_EntityType_Player) {
            speed = std::max(speed, 10.f);
        }
        action::do_move(*this, *move_to, move_until_dis, tmpDeltaTime, speed);
    }

    if (type == EntityProto_EntityType_Player &&
        action.type == EntityProto_ActionType_Attack && !action.empty()) {
        auto t = static_cast<action::Attack *>(action.data.back().get());
        if (t->target->action.type == EntityProto_ActionType_Death ||
            t->target->action.type == EntityProto_ActionType_Invisible) {
            // 攻击目标不存在
            action = action::comb::Idle();
            next_action = action::comb::Idle();
        }
    }
    action.run(deltaTime);
    if (type == EntityProto_EntityType_Player && action.empty() &&
        !next_action.empty()) {
        if (next_action.type ==
            EntityProto_ActionType_Attack) {  // 不断平 A，复制 next_action
                                              // 而非移动
            auto t =
                static_cast<action::Attack *>(next_action.data.back().get());
            action = action::comb::Attack(t->entity, t->target, t->scene);
        } else {
            action = std::move(next_action);
        }
    }

    Acd.add(-deltaTime);
    Qcd.add(-deltaTime);
    Wcd.add(-deltaTime);
    Ecd.add(-deltaTime);
    Rcd.add(-deltaTime);

    if (blood.now == 0) {
        if (type == EntityProto_EntityType_Satchel &&
            action.type != EntityProto_ActionType_Invisible) {
            log_info("Satchel launch");
            scene->map->set_working(id);
            action = action::comb::SatchelLaunch(shared_from_this(), scene);
        }
        if (Config::is_enemy(type) &&
            action.type != EntityProto_ActionType_Death) {
            if (type == EntityProto_EntityType_Melee) {
                action = action::comb::Death(shared_from_this(), 1.4f, scene);
            } else if (type == EntityProto_EntityType_Urgot) {
                action = action::comb::Death(shared_from_this(), 3.f, scene);
            }
        }
        if (type == EntityProto_EntityType_Nexus) {
            scene->finished = true;
        }
    }
    // satchel
    if (type == EntityProto_EntityType_Satchel) {
        if (action.type != EntityProto_ActionType_Invisible) {
            if (height < 0) {
                height += deltaTime * Config::wall_speed();
                height = std::min(height, 0.f);
            }
        } else {
            if (height > -wall::Length - 0.1f) {
                height -= deltaTime * Config::wall_speed();
                height = std::max(height, -wall::Length - 0.1f);
            }
        }
    }
    // nexus
    if (type == EntityProto_EntityType_Nexus) {
        if (action.type != EntityProto_ActionType_Invisible) {
            if (height < 0) {
                height += deltaTime * Config::wall_speed();
                height = std::min(height, 0.f);
            }
        } else {
            if (height > -7 - 0.1f) {
                height -= deltaTime * Config::wall_speed();
                height = std::max(height, -7 - 0.1f);
            }
        }
    }
}

void Entity::print() const {
    if (type == EntityProto_EntityType_Player) {
        log_info("entity [id={}, type={}, action={}]", id, (int)type,
                 action.type);
    }
}

EntityProto Entity::proto() const {
    EntityProto proto;
    proto.set_id(id);
    proto.set_rotation(rotation);
    proto.set_type(type);
    *proto.mutable_blood() = blood.proto();
    proto.set_action(Config::action_proto(*this));

    *proto.mutable_position() =
        Vector::to_proto(vec3(position->x, height, position->y));
    *proto.mutable_velocity() = Vector::to_proto(velocity);
    return proto;
}

void Entity::rotate_to(const vec2 &position) {
    vec2 delta = position - *this->position;
    rotation = atan2f(delta.x, delta.y);
}

float Entity::attack_radius() const { return Config::attack_radius(*this); }