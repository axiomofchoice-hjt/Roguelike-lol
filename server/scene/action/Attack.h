#pragma once

#include "Action.h"

class Scene;

namespace action {
/// 玩家一瞬间的平 A 动作
class Attack : public Action {
   public:
    shared<Entity> target;
    Scene *scene;

    Attack(shared<Entity> entity, shared<Entity> target, Scene *scene)
        : Action(entity), target(target), scene(scene) {}
    bool run(float &deltaTime) override;
};
}  // namespace action