#pragma once

#include "Action.h"

class Scene;

namespace action {
/// 销毁自身
class Destroy : public Action {
   public:
    Scene *scene;
    Destroy(shared<Entity> entity, Scene *scene)
        : Action(entity), scene(scene) {}
    bool run(float &deltaTime) override;
};
}  // namespace action