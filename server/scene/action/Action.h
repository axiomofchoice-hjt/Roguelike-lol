#pragma once

#include <functional>
#include <list>
#include <memory>

#include "proto/Scene.pb.h"
#include "tools/basic.h"

class Entity;

namespace action {
/// 所有动作类的基类
class Action {
   public:
    /// 发起动作的实体
    shared<Entity> entity;
    Action(shared<Entity> entity) : entity(entity) {}
    /**
     * @brief 执行动作
     *
     * @param deltaTime 提供的时间
     * @return true 还有时间剩下
     * @return false 没有时间剩下
     */
    virtual bool run(float &deltaTime) = 0;
};

/// 多个动作组成的动作序列
class ActionList {
   public:
    /// 动作序列
    std::list<uptr<Action>> data;
    /// 动作类型
    EntityProto_ActionType type;
    ActionList() : data(), type(EntityProto_ActionType_Undefined) {}
    template <typename T, typename... Args>
    void append(Args &&...args) {
        data.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    }
    void clear();
    bool empty() const;
    /// 执行动作序列
    void run(float deltaTime);
};
}  // namespace action