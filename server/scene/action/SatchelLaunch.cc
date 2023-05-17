#include "SatchelLaunch.h"

#include "proto/Scene.pb.h"
#include "scene/Config.h"
#include "scene/EnemyAI.h"
#include "scene/Scene.h"
#include "tools/UUID.h"

namespace action {
SatchelLaunch::SatchelLaunch(shared<Entity> entity, Scene *scene)
    : Action(entity), scene(scene) {}

bool SatchelLaunch::run(float &deltaTime) {
    auto &room = *scene->map->find_room_by_satchel(entity->id);
    for (int i = 0; i < 3; i++) {
        shared<Entity> enemy =
            scene->add_entity(UUID::get(), EntityProto_EntityType_Melee);
        *enemy->position =
            vec2(Config::room_size() * (room.x + Rand::f(-0.45, 0.45)),
                 Config::room_size() * (room.y + Rand::f(-0.45, 0.45)));
        enemy->AI = std::make_unique<EnemyAI>(enemy, scene);
    }
    for (int i = 0; i < 2; i++) {
        shared<Entity> enemy =
            scene->add_entity(UUID::get(), EntityProto_EntityType_Urgot);
        *enemy->position =
            vec2(Config::room_size() * (room.x + Rand::f(-0.45, 0.45)),
                 Config::room_size() * (room.y + Rand::f(-0.45, 0.45)));
        enemy->AI = std::make_unique<EnemyAI>(enemy, scene);
    }
    return true;
}
}  // namespace action