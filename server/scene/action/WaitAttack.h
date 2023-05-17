#pragma once

#include "Action.h"

class Entity;

namespace action {
class WaitAttack : public Action {
   public:
    shared<Entity> target;

    WaitAttack(shared<Entity> entity, shared<Entity> target)
        : Action(entity), target(target) {}
    bool run(float &deltaTime) override;
};
}  // namespace action