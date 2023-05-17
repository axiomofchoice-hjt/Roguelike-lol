#include "KaisaR.h"

#include "comb.h"
#include "scene/Entity.h"
#include "scene/Scene.h"
#include "tools/UUID.h"

namespace action {
bool KaisaR::run(float &deltaTime) {
    constexpr float a = 50.f;
    constexpr float e = 15.f;
    float speed =
        std::sqrt(2 * a * geo::distance(*entity->position, position) + e * e);
    return do_move(*entity, position, 0.01f, deltaTime, speed);
}
}  // namespace action