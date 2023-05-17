#pragma once

#include "Action.h"
#include "scene/Entity.h"
#include "tools/Vector.h"

class Scene;

namespace action {
/// 释放 Q 子弹
class KaisaQ : public Action {
   public:
    shared<Entity> target;
    float ratio;
    Scene *scene;

    KaisaQ(shared<Entity> entity, shared<Entity> target, float ratio,
           Scene *scene)
        : Action(entity), target(target), ratio(ratio), scene(scene) {}
    bool run(float &deltaTime) override;
};
}  // namespace action