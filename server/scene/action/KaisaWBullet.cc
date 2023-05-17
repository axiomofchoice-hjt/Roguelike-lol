#include "KaisaWBullet.h"

#include "scene/Config.h"
#include "scene/Entity.h"
#include "scene/Scene.h"

namespace action {
bool KaisaWBullet::run(float &deltaTime) {
    shared<Entity> entity = this->entity;
    for (shared<Entity> target : scene->entities) {
        if (Config::is_enemy(target->type) &&
            target->action.type != EntityProto_ActionType_Death &&
            geo::distance(*entity->position, *target->position) <=
                entity->attack_radius()) {
            target->blood.add(-10);
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