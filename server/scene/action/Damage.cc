#include "Damage.h"

#include "comb.h"
#include "scene/Entity.h"
#include "scene/Scene.h"

namespace action {
bool Damage::run(float &deltaTime) {
    shared<Entity> target = this->target;
    target->blood.add(-value);
    return true;
}
}  // namespace action