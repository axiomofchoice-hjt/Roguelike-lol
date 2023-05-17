#pragma once

#include "Action.h"
#include "tools/Vector.h"

class Entity;
class Scene;

namespace action {
/// 释放 W 子弹
class KaisaW : public Action {
   public:
    vec2 position;
    Scene *scene;

    KaisaW(shared<Entity> entity, vec2 position, Scene *scene)
        : Action(entity), position(position), scene(scene) {}
    bool run(float &deltaTime) override;
};
}  // namespace action