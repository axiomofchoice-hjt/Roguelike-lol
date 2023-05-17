#include "KaisaQBullet.h"

#include <algorithm>

#include "scene/Entity.h"
#include "scene/Scene.h"

namespace action {
bool KaisaQBullet::run(float &deltaTime) {
    shared<Entity> entity = this->entity;
    vec2 pos(entity->position->x, entity->position->y);
    init_velocity_ratio = std::max(0.f, init_velocity_ratio - deltaTime * 3.f);
    float dist = geo::distance(*target, pos);
    if (dist < 0.001) {
        return true;
    }
    vec2 velocity =
        init_velocity * init_velocity_ratio +
        geo::normalize(*target - pos) * 30.f * (1 - init_velocity_ratio);

    if (dist < geo::length(velocity) * deltaTime) {
        deltaTime -= dist / geo::length(velocity);
        return true;
    }

    *entity->position += deltaTime * velocity;
    entity->rotate_to(*this->target);
    deltaTime = 0;
    return false;
}
}  // namespace action