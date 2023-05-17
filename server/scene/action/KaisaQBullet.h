#pragma once

#include "Action.h"
#include "tools/Vector.h"

class Scene;

namespace action {
class KaisaQBullet : public Action {
   public:
    shared<vec2> target;
    vec2 init_velocity;
    float init_velocity_ratio;

    KaisaQBullet(shared<Entity> entity, shared<vec2> position,
                 vec2 init_velocity)
        : Action(entity),
          target(position),
          init_velocity(init_velocity),
          init_velocity_ratio(1) {}
    bool run(float &deltaTime) override;
};
}  // namespace action