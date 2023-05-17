#pragma once

#include "proto/Scene.pb.h"
#include "tools/basic.h"

class Entity;

namespace Config {
/// 速度
float speed(const Entity &entity);

/// 当前状态是否可移动
bool movable(const Entity &entity);

/// 攻击半径
float attack_radius(const Entity &entity);

/// 给客户端的动作
EntityProto_ActionType action_proto(const Entity &entity);

/// 判断敌人
bool is_enemy(EntityProto_EntityType type);

inline float melee_attack_distance() { return 2; }
inline float melee_attack_speed() { return 4; }
inline float room_size() { return 30; }
inline float wall_speed() { return 5; }
}  // namespace Config