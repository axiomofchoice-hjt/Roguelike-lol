#include "EnemyAI.h"

#include "Config.h"
#include "Scene.h"
#include "action/comb.h"
#include "geo/geo.h"
#include "geo/segment2d.h"
#include "geo/vec2.h"
#include "scene/Wall.h"
#include "tools/Vector.h"
#include "tools/basic.h"
#include "tools/log.h"

EnemyAI::EnemyAI(shared<Entity> entity, Scene *scene)
    : sleep(0.5f), entity(entity), scene(scene) {
    entity->action = action::comb::Idle();
}

void EnemyAI::run(float deltaTime) {
    if (entity->action.type == EntityProto_ActionType_Death) {
        return;
    }
    if (sleep > deltaTime) {
        sleep -= deltaTime;
        return;
    }
    deltaTime -= sleep;
    if (entity->action.type == EntityProto_ActionType_MeleeAttack) {
        return;
    }
    if (entity->action.type == EntityProto_ActionType_Attack) {
        return;
    }
    int t = Rand::d(3);
    if (t == 0) {
        entity->action = action::comb::Idle();
        sleep = Rand::f(1, 2);
    } else if (t == 1 && entity->Acd.now == 0) {
        shared<Entity> player;
        for (auto i : scene->entities) {
            if (i->type == EntityProto_EntityType_Player &&
                (player == nullptr ||
                 geo::distance(*entity->position, *i->position) <
                     geo::distance(*entity->position, *player->position))) {
                player = i;
            }
        }
        if (player != nullptr) {
            if (entity->type == EntityProto_EntityType_Melee) {
                entity->rotate_to(*player->position);
                entity->action =
                    action::comb::MeleeAttack(entity, player, scene);
            } else {
                entity->rotate_to(*player->position);
                entity->action =
                    action::comb::UrgotAttack(entity, player, scene);
            }
        }
    } else {
        vec2 to;
        bool flag = false;
        for (int i = 0; i < 100; i++) {
            to = *entity->position + vec2(Rand::f(-10, 10), Rand::f(-10, 10));
            if (geo::distance(*entity->position, to) <= 10.f &&
                scene->map->working_room &&
                scene->map->working_room->in_area(to)) {
                flag = true;
                break;
            }
        }
        if (flag) {
            entity->action =
                action::comb::Move(entity, std::make_shared<vec2>(to));
        } else {
            log_warn("find route failed");
        }
        sleep = Rand::f(2, 3);
    }
}