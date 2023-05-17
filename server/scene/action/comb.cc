#include "comb.h"

#include "Attack.h"
#include "Custom.h"
#include "Damage.h"
#include "Destroy.h"
#include "KaisaQ.h"
#include "KaisaQBullet.h"
#include "KaisaR.h"
#include "KaisaW.h"
#include "KaisaWBullet.h"
#include "MeleeAttack.h"
#include "SatchelLaunch.h"
#include "UrgotAttack.h"
#include "UrgotBullet.h"
#include "WaitAttack.h"
#include "scene/Config.h"
#include "scene/Scene.h"

namespace action {
namespace comb {
ActionList Idle() { return ActionList(); }

ActionList Move(shared<Entity> entity, shared<vec2> position) {
    entity->move_to = position;
    entity->move_until_dis = 0.01;
    return Idle();
}

ActionList Attack(shared<Entity> entity, shared<Entity> target, Scene *scene) {
    ActionList action;
    action.type = EntityProto_ActionType_Attack;
    entity->move_to = target->position;
    entity->move_until_dis = entity->attack_radius() - 0.01f;
    action.append<action::WaitAttack>(entity, target);
    action.append<action::Wait>(entity, 0.07f, target->position);
    action.append<action::Attack>(entity, target, scene);
    return action;
}

ActionList Bullet(shared<Entity> entity, shared<Entity> target, Scene *scene) {
    ActionList action;
    action.append<action::WaitAttack>(entity, target);
    action.append<action::Damage>(entity, target, 20);
    action.append<action::Destroy>(entity, scene);
    return action;
}

ActionList KaisaQBullet(shared<Entity> entity, shared<Entity> target,
                        float ratio, Scene *scene) {
    ActionList action;
    vec2 to_raw = geo::normalize(*entity->position - *target->position);
    vec2 o = vec2(to_raw.y, -to_raw.x) * (ratio * 2.f - 1.f);
    action.append<action::KaisaQBullet>(entity, target->position, o * 15.f);
    action.append<action::Damage>(entity, target, 2);
    action.append<action::Destroy>(entity, scene);
    return action;
}

ActionList KaisaQ(shared<Entity> entity, Scene *scene) {
    ActionList action;
    action.type = EntityProto_ActionType_KaisaQ;
    const u32 bullet_count = 12;
    std::vector<float> ratios(bullet_count, 0.f);
    for (u32 i = 0; i < bullet_count; i++) {
        ratios[i] = i / (bullet_count - 1.f);
    }
    std::shuffle(ratios.begin(), ratios.end(), Rand::gen);
    std::vector<shared<Entity>> targets;
    for (shared<Entity> target : scene->entities) {
        if (Config::is_enemy(target->type) &&
            target->action.type != EntityProto_ActionType_Death &&
            geo::distance(*target->position, *entity->position) <=
                entity->attack_radius()) {
            targets.push_back(target);
        }
    }
    if (targets.empty()) {
        return action;
    }
    action.append<Custom>([entity](float &) {
        entity->Qcd.now = 3;
        return true;
    });
    std::shuffle(targets.begin(), targets.end(), Rand::gen);
    for (u32 i = 0; i < bullet_count; i++) {
        action.append<action::Wait>(entity, 0.05f);
        action.append<action::KaisaQ>(entity, targets[i % targets.size()],
                                      ratios[i], scene);
    }
    return action;
}

ActionList KaisaWBullet(shared<Entity> entity, Scene *scene) {
    ActionList action;
    action.append<action::KaisaWBullet>(entity, scene);
    action.append<action::Destroy>(entity, scene);
    return action;
}

ActionList KaisaW(shared<Entity> entity, vec2 position, Scene *scene) {
    ActionList action;
    action.type = EntityProto_ActionType_KaisaW;
    action.append<Custom>([entity](float &) {
        entity->Wcd.now = 3;
        return true;
    });
    action.append<action::Wait>(entity, 0.5f, std::make_shared<vec2>(position));
    action.append<action::KaisaW>(entity, position, scene);
    action.append<action::Wait>(entity, 0.1f, std::make_shared<vec2>(position));
    return action;
}

ActionList KaisaE(shared<Entity> entity) {
    ActionList action;
    action.type = EntityProto_ActionType_KaisaE;
    action.append<Custom>([entity](float &) {
        entity->Ecd.now = 4;
        return true;
    });
    action.append<action::Wait>(entity, 0.5);
    return action;
}

ActionList KaisaR(shared<Entity> entity, vec2 position) {
    ActionList action;
    action.type = EntityProto_ActionType_KaisaR;
    action.append<Custom>([entity](float &) {
        entity->Rcd.now = 5;
        return true;
    });
    action.append<action::KaisaR>(entity, position);
    return action;
}

ActionList MeleeAttack(shared<Entity> entity, shared<Entity> target,
                       Scene *scene) {
    ActionList action;
    action.type = EntityProto_ActionType_MeleeAttack;
    action.append<action::Wait>(entity, 0.5f);
    action.append<action::MeleeAttack>(entity, *target->position, scene);
    action.append<action::Wait>(entity, 0.5f);
    return action;
}

ActionList SatchelLaunch(shared<Entity> entity, Scene *scene) {
    ActionList action;
    action.type = EntityProto_ActionType_Invisible;
    action.append<action::Wait>(entity, 1.5f);
    action.append<action::SatchelLaunch>(entity, scene);
    action.append<action::Wait>(entity, INFINITY);
    return action;
}

ActionList Death(shared<Entity> entity, float animationTime, Scene *scene) {
    ActionList action;
    action.type = EntityProto_ActionType_Death;
    action.append<action::Wait>(entity, animationTime);
    action.append<action::Destroy>(entity, scene);
    action.append<action::Wait>(entity, INFINITY);
    return action;
}

ActionList Invisible(shared<Entity> entity) {
    ActionList action;
    action.type = EntityProto_ActionType_Invisible;
    action.append<action::Wait>(entity, INFINITY);
    return action;
}

ActionList UrgotBullet(shared<Entity> entity, Scene *scene) {
    ActionList action;
    action.append<action::UrgotBullet>(entity, scene);
    action.append<action::Destroy>(entity, scene);
    return action;
}

ActionList UrgotAttack(shared<Entity> entity, shared<Entity> target,
                       Scene *scene) {
    ActionList action;
    action.type = EntityProto_ActionType_Attack;
    action.append<action::Wait>(entity, 0.5f);
    action.append<action::UrgotAttack>(
        entity,
        *entity->position +
            geo::normalize(*target->position - *entity->position) * 27,
        scene);
    return action;
}
}  // namespace comb
}  // namespace action