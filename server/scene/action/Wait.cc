#include "Wait.h"

#include "scene/Entity.h"

namespace action {
bool Wait::run(float &deltaTime) {
    if (face_to != nullptr) {
        entity->rotate_to(*face_to);
    }
    if (deltaTime >= time) {
        deltaTime -= time;
        return true;
    } else {
        time -= deltaTime;
        deltaTime = 0;
        return false;
    }
}
}  // namespace action