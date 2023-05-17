#pragma once

#include "Action.h"
#include "tools/Vector.h"

class Entity;

namespace action {
class Wait : public Action {
   public:
    float time;
    shared<vec2> face_to;
    Wait(shared<Entity> entity, float time, shared<vec2> face_to = nullptr)
        : Action(entity), time(time), face_to(face_to) {}
    bool run(float &deltaTime) override;
};
}  // namespace action