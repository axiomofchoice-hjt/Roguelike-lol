#pragma once

#include "Action.h"
#include "tools/Vector.h"
#include "tools/basic.h"

class Entity;

namespace action {
bool do_move(Entity &entity, vec2 move_to, float until_dis, float &deltaTime,
             float speed);

class Move : public Action {
   public:
    std::shared_ptr<vec2> move_to;
    float until_dis;
    shared<vec2> face_to;
    Move(shared<Entity> entity, std::shared_ptr<vec2> move_to, float until_dis)
        : Action(entity), move_to(move_to), until_dis(until_dis) {}
    bool run(float &deltaTime) override;
};
}  // namespace action