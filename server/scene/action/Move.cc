#include "Move.h"

#include "scene/Config.h"
#include "scene/Entity.h"

namespace action {
bool do_move(Entity &entity, vec2 to, float until_dis, float &deltaTime,
             float speed) {
    entity.moving = false;
    float dis = geo::length(*entity.position - to);
    if (dis <= until_dis) {
        entity.velocity = vec3();
        return true;
    }
    bool ok = speed * deltaTime >= dis - until_dis;
    float step = std::min(speed * deltaTime, dis - until_dis);
    vec2 delta = geo::normalize(to - *entity.position);

    *entity.position = *entity.position + delta * step;
    entity.rotation = atan2(delta.x, delta.y);
    entity.moving = !ok;
    deltaTime -= step / speed;
    if (!ok) {
        auto t = delta * speed;
        entity.velocity.x = t.x;
        entity.velocity.z = t.y;
    }
    return ok;
}

bool Move::run(float &deltaTime) {
    entity->move_to = move_to;
    entity->move_until_dis = until_dis;
    return true;
}
}  // namespace action