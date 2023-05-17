#pragma once

#include <cfloat>
#include <memory>

#include "Action.h"
#include "Move.h"
#include "Wait.h"
#include "tools/Vector.h"
#include "tools/basic.h"

class Scene;
class Entity;

namespace action {
namespace comb {
/// 无动作
ActionList Idle();
/// 移动
ActionList Move(shared<Entity> entity, shared<vec2> position);
/// 角色的平 A
ActionList Attack(shared<Entity> entity, shared<Entity> target, Scene *scene);
/// 角色平 A 的子弹
ActionList Bullet(shared<Entity> entity, shared<Entity> target, Scene *scene);
/// 角色 Q 技能子弹
ActionList KaisaQBullet(shared<Entity> entity, shared<Entity> target,
                        float ratio, Scene *scene);
/// 角色 Q 技能
ActionList KaisaQ(shared<Entity> entity, Scene *scene);
/// 角色 W 技能子弹
ActionList KaisaWBullet(shared<Entity> entity, Scene *scene);
/// 角色 W 技能
ActionList KaisaW(shared<Entity> entity, vec2 position, Scene *scene);
/// 角色 E 技能
ActionList KaisaE(shared<Entity> entity);
/// 角色 R 技能
ActionList KaisaR(shared<Entity> entity, vec2 position);

/// 怪物 Melee 攻击
ActionList MeleeAttack(shared<Entity> entity, shared<Entity> target,
                       Scene *scene);
/// 房间机关的启动
ActionList SatchelLaunch(shared<Entity> entity, Scene *scene);
/// 死亡
ActionList Death(shared<Entity> entity, float animationTime, Scene *scene);
/// 不可见
ActionList Invisible(shared<Entity> entity);
/// Urgot 子弹
ActionList UrgotBullet(shared<Entity> entity, Scene *scene);
/// Urgot 攻击
ActionList UrgotAttack(shared<Entity> entity, shared<Entity> target,
                       Scene *scene);
}  // namespace comb
}  // namespace action