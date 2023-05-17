#include "UrgotBullet.h"

#include "scene/Entity.h"
#include "scene/Scene.h"

namespace action {
bool UrgotBullet::run(float &deltaTime) {
    shared<Entity> entity = this->entity;
    for (shared<Entity> target : scene->entities) {
        if (target->type == EntityProto_EntityType_Player &&
            target->action.type != EntityProto_ActionType_Death &&
            geo::distance(*entity->position, *target->position) <=
                entity->attack_radius()) {
            target->blood.add(-30);
            return true;
        }
    }
    if (!entity->moving) {
        return true;
    }
    deltaTime = 0;
    return false;
}
}  // namespace action