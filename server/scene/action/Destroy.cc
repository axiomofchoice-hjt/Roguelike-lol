#include "Destroy.h"

#include "scene/Config.h"
#include "scene/Entity.h"
#include "scene/Scene.h"
#include "tools/basic.h"

namespace action {
bool Destroy::run(float &deltaTime) {
    if (Config::is_enemy(entity->type)) {
        scene->enemy_count--;
        if (scene->enemy_count == 0) {
            scene->map->set_ok();
        }
    }
    entity->removed = true;
    return true;
}
}  // namespace action