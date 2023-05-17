#include "Attack.h"

#include "comb.h"
#include "scene/Entity.h"
#include "scene/Scene.h"
#include "tools/UUID.h"

namespace action {
bool Attack::run(float &deltaTime) {
    entity->Acd.now = 0.5f;  // 设置平 A 后摇

    shared<Entity> bullet =
        scene->add_entity(UUID::get(), EntityProto_EntityType_Bullet);
    bullet->position = std::make_shared<vec2>(*entity->position);
    bullet->action = action::comb::Bullet(bullet, target, scene);
    bullet->move_to = target->position;
    bullet->move_until_dis = 0.1;
    return true;
}
}  // namespace action