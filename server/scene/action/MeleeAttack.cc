#include "MeleeAttack.h"

#include "Move.h"
#include "scene/Config.h"
#include "scene/Entity.h"
#include "scene/Scene.h"

namespace action {
MeleeAttack::MeleeAttack(shared<Entity> entity, vec2 target, Scene *scene)
    : Action(entity),
      to(*entity->position + geo::normalize(target - *entity->position) *
                                 Config::melee_attack_distance()),
      scene(scene) {}

bool MeleeAttack::run(float &deltatime) {
    entity->Acd.now = 5;
    for (auto &i : scene->entities) {
        if (!attacked.contains(i->id) &&
            i->type == EntityProto_EntityType_Player &&
            geo::distance(*i->position, *entity->position) <=
                Config::attack_radius(*entity)) {
            attacked.insert(i->id);
            i->blood.add(-Config::damage(entity->type));
        }
    }
    return do_move(*entity, to, 0.01f, deltatime, Config::melee_attack_speed());
}
}  // namespace action