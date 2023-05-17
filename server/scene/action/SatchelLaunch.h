#pragma once

#include "Action.h"
#include "tools/Vector.h"

class Entity;
class Scene;

namespace action {
class SatchelLaunch : public Action {
   public:
    Scene *scene;

    SatchelLaunch(shared<Entity> entity, Scene *scene);
    bool run(float &deltaTime) override;
};
}  // namespace action