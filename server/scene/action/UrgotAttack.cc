#include "UrgotAttack.h"

#include "comb.h"
#include "scene/Entity.h"
#include "scene/Scene.h"
#include "tools/UUID.h"

namespace action {
bool UrgotAttack::run(float &deltaTime) {
    entity->Acd.now = 5;
    shared<Entity> bullet =
        scene->add_entity(UUID::get(), EntityProto_EntityType_UrgotBullet);
    bullet->position = std::make_shared<vec2>(*entity->position);
    bullet->action = action::comb::UrgotBullet(bullet, scene);
    bullet->move_to = std::make_shared<vec2>(position);
    bullet->move_until_dis = 0.01f;
    return true;
}
}  // namespace action