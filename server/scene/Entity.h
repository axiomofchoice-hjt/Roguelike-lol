#pragma once

#include <list>

#include "EnemyAI.h"
#include "action/Action.h"
#include "proto/Scene.pb.h"
#include "tools/Vector.h"
#include "tools/basic.h"

/// 实体
class Entity : public std::enable_shared_from_this<Entity> {
   public:
    /// 唯一标识
    u64 id;
    /// 位置
    shared<vec2> position;
    /// 高度
    float height;
    /// 速度
    vec3 velocity;
    /// 旋转角度
    float rotation;
    /// 实体类型
    EntityProto::EntityType type;
    /// 真正执行的动作序列
    action::ActionList action;
    /// 下一步的动作序列
    action::ActionList next_action;
    /// 移动目标
    shared<vec2> move_to;
    /// 移动直到在目标多少距离内
    float move_until_dis;
    /// 正在移动
    bool moving;
    /// 碰撞半径
    float collide_radius;
    /// 删除标志
    bool removed;
    /// 血量
    LimitValue blood;
    /// 左 / 右手交替攻击
    bool attack_hand;
    /// 平 A 的冷却
    LimitValue Acd;
    /// Q 技能的冷却
    LimitValue Qcd;
    /// W 技能的冷却
    LimitValue Wcd;
    /// E 技能的冷却
    LimitValue Ecd;
    /// R 技能的冷却
    LimitValue Rcd;
    /// 敌人 AI
    uptr<EnemyAI> AI;

    Entity(u64 id, EntityProto::EntityType type);
    ~Entity();
    void update(const float deltaTime, Scene *scene);
    void print() const;
    EntityProto proto() const;

    void rotate_to(const vec2 &position);
    float attack_radius() const;
};