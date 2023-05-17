#pragma once

#include "Action.h"

class Scene;

namespace action {
/// 造成伤害
class Damage : public Action {
   public:
    shared<Entity> target;
    float value;

    Damage(shared<Entity> entity, shared<Entity> target, float value)
        : Action(entity), target(target), value(value) {}
    bool run(float &deltaTime) override;
};
}  // namespace action