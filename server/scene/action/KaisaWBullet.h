#pragma once

#include "Action.h"

class Entity;
class Scene;

namespace action {
class KaisaWBullet : public Action {
   public:
    Scene *scene;

    KaisaWBullet(shared<Entity> entity, Scene *scene)
        : Action(entity), scene(scene) {}
    bool run(float &deltaTime) override;
};
}  // namespace action