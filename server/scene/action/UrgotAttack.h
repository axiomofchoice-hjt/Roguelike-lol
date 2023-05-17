#pragma once

#include "Action.h"
#include "tools/Vector.h"

class Entity;
class Scene;

namespace action {
class UrgotAttack : public Action {
   public:
    vec2 position;
    Scene *scene;

    UrgotAttack(shared<Entity> entity, vec2 position, Scene *scene)
        : Action(entity), position(position), scene(scene) {}
    bool run(float &deltaTime) override;
};
}  // namespace action