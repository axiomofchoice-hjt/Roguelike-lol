#include "WaitAttack.h"

#include "scene/Entity.h"

namespace action {
bool WaitAttack::run(float &deltaTime) {
    shared<Entity> entity = this->entity;
    shared<Entity> target = this->target;
    if (!entity->moving) {
        entity->rotate_to(*target->position);
    }
    if (geo::distance(*entity->position, *target->position) >=
        entity->attack_radius()) {
        deltaTime = 0;
        return false;
    }
    if (deltaTime < entity->Acd.now) {
        deltaTime = 0;
        return false;
    }
    deltaTime -= entity->Acd.now;
    entity->attack_hand ^= true;
    return true;
}
}  // namespace action