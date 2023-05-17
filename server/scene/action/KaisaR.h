#pragma once

#include "Action.h"
#include "tools/Vector.h"

class Entity;
class Scene;

namespace action {
class KaisaR : public Action {
   public:
    vec2 position;

    KaisaR(shared<Entity> entity, vec2 position)
        : Action(entity), position(position) {}
    bool run(float &deltaTime) override;
};
}  // namespace action