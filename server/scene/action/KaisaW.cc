#include "KaisaW.h"

#include "comb.h"
#include "scene/Entity.h"
#include "scene/Scene.h"
#include "tools/UUID.h"

namespace action {
bool KaisaW::run(float &deltaTime) {
    shared<Entity> bullet =
        scene->add_entity(UUID::get(), EntityProto_EntityType_KaisaWBullet);
    bullet->position = std::make_shared<vec2>(*entity->position);
    bullet->action = action::comb::KaisaWBullet(bullet, scene);
    bullet->move_to = std::make_shared<vec2>(position);
    bullet->move_until_dis = 0.01f;
    return true;
}
}  // namespace action