#include "KaisaQ.h"

#include "comb.h"
#include "scene/Entity.h"
#include "scene/Scene.h"
#include "tools/UUID.h"

namespace action {
bool KaisaQ::run(float &deltaTime) {
    shared<Entity> bullet =
        scene->add_entity(UUID::get(), EntityProto_EntityType_KaisaQBullet);
    bullet->position = std::make_shared<vec2>(
        *entity->position +
        geo::normalize(*entity->position - *target->position) * 1.f);
    bullet->action = action::comb::KaisaQBullet(bullet, target, ratio, scene);
    return true;
}
}  // namespace action