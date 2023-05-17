#pragma once

#include "Action.h"
#include "tools/Vector.h"

class Scene;

namespace action {
class MeleeAttack : public Action {
   public:
    vec2 to;
    Scene *scene;
    SmallSet<u64> attacked;

    MeleeAttack(shared<Entity> entity, vec2 target, Scene *scene);
    bool run(float &deltaTime) override;
};
}  // namespace action