#include "Scene.h"

#include <fmt/core.h>

#include <algorithm>
#include <climits>

#include "Config.h"
#include "action/comb.h"
#include "proto/Scene.pb.h"
#include "scene/Entity.h"
#include "scene/Wall.h"
#include "tools/UUID.h"
#include "tools/basic.h"
#include "tools/log.h"

Scene::Scene() : update_count(0) { init(); }

void Scene::init() {
    std::vector<shared<Entity>> tmp;
    for (auto i : entities) {
        if (i->type != EntityProto_EntityType_Player) {
            i->removed = true;
        }
    }
    walls.clear();
    finished = false;
    enemy_count = 0;

    world_seed = Rand::gen();
    map = std::make_unique<map::Map>(this);
}

shared<Entity> Scene::add_entity(u64 id, EntityProto::EntityType type) {
    // if (type == EntityProto_EntityType_Satchel) {
    //     log_info("add satchel id={}", id);
    // }
    shared<Entity> entity = std::make_shared<Entity>(id, type);
    add_entities.push_back(entity);
    if (Config::is_enemy(type)) {
        enemy_count++;
    }
    return entity;
}

shared<Entity> Scene::find(u64 id) const {
    auto ret =
        std::find_if(entities.begin(), entities.end(),
                     [id](shared<Entity> entity) { return entity->id == id; });
    if (ret == entities.end()) {
        ret = std::find_if(
            add_entities.begin(), add_entities.end(),
            [id](shared<Entity> entity) { return entity->id == id; });

        if (ret == add_entities.end()) {
            return nullptr;
        }
    }
    return *ret;
}

shared<wall::Wall> Scene::find_wall(u64 id) {
    auto ret = std::find_if(walls.begin(), walls.end(),
                            [id](shared<wall::Wall> w) { return w->id == id; });
    if (ret == walls.end()) {
        log_panic("Scene::find_wall no such id={}\n", id);
    }
    return *ret;
}

/// 处理接收
void Scene::receive(u64 id, const MessageProto &msg) {
    shared<Entity> player = find(id);
    if (msg.type() == MessageProto_Type_Move) {
        vec2 pos = Vector::from_proto(msg.position());
        if (player->action.type == EntityProto_ActionType_Attack) {
            player->action.clear();
        }
        player->next_action.clear();
        player->move_to = std::make_shared<vec2>(pos);
        player->move_until_dis = 0.01;
        player->next_action = action::comb::Move(player, player->move_to);
    } else if (msg.type() == MessageProto_Type_Attack) {
        if (player->action.type == EntityProto_ActionType_Attack) {
            player->action.clear();
        }
        auto to = find(msg.target());
        if (to != nullptr) {
            player->next_action = action::comb::Attack(player, to, this);
        }
    } else if (msg.type() == MessageProto_Type_Q) {  // Q 技能
        if (player->Qcd.now == 0.f) {
            if (player->action.type == EntityProto_ActionType_Attack) {
                player->action.clear();
            }
            player->next_action = action::comb::KaisaQ(player, this);
        }
    } else if (msg.type() == MessageProto_Type_W) {
        if (player->Wcd.now == 0.f) {
            if (player->action.type == EntityProto_ActionType_Attack) {
                player->action.clear();
            }
            vec2 pos = Vector::from_proto(msg.position());
            pos = *player->position +
                  geo::normalize(pos - *player->position) * 18.f;
            player->next_action = action::comb::KaisaW(player, pos, this);
        }
    } else if (msg.type() == MessageProto_Type_E) {
        if (player->Ecd.now == 0.f) {
            if (player->action.type == EntityProto_ActionType_Attack) {
                player->action.clear();
            }
            player->next_action = action::comb::KaisaE(player);
        }
    } else if (msg.type() == MessageProto_Type_R) {
        if (player->Rcd.now == 0.f) {
            if (player->action.type == EntityProto_ActionType_Attack) {
                player->action.clear();
            }
            vec2 pos = Vector::from_proto(msg.position());
            player->next_action = action::comb::KaisaR(player, pos);
            player->move_to = std::make_shared<vec2>(pos);
        }
    } else if (msg.type() == MessageProto_Type_Test) {
        print();
    } else if (msg.type() == MessageProto_Type_ClearEnemies) {
        for (auto i : entities) {
            if (Config::is_enemy(i->type)) {
                i->blood.now = 0;
            }
        }
    }
}

void Scene::update(float deltaTime) {
    for (shared<Entity> &i : entities) {
        if (i->AI != nullptr) {
            i->AI->run(deltaTime);
        }
    }
    for (shared<Entity> &i : entities) {
        i->update(deltaTime, this);
        if (i->type == EntityProto_EntityType_Player &&
            i->action.type != EntityProto_ActionType_KaisaR) {
            map->block_player(*i);
        }
    }
    for (auto &i : walls) {
        i->update(deltaTime, this);
    }
    entities.erase(std::remove_if(entities.begin(), entities.end(),
                                  [](const shared<Entity> &entity) {
                                      return entity->removed;
                                  }),
                   entities.end());
    for (shared<Entity> &i : add_entities) {
        entities.push_back(i);
    }
    add_entities.clear();
    update_count++;
    if (finished) {
        init();
    }
}

void Scene::print() const {
    for (shared<Entity> i : entities) {
        i->print();
    }
    for (const shared<wall::Wall> &i : walls) {
        i->print();
    }
}

SceneProto Scene::proto() const {
    SceneProto proto;
    proto.set_world_seed(world_seed);
    proto.set_working(map->working_room != nullptr);

    for (shared<Entity> entity : entities) {
        *proto.add_entities() = entity->proto();
    }

    for (auto &wall : walls) {
        *proto.add_walls() = wall->proto();
    }

    return proto;
}

void Scene::others_to_proto(SceneProto &proto, u64 id) const {
    shared<Entity> entity = find(id);
    if (entity != nullptr) {
        proto.set_id(id);
        proto.set_attack_radius(entity->attack_radius());
        proto.set_acd(entity->Acd.now);
        proto.set_qcd(entity->Qcd.now);
        proto.set_wcd(entity->Wcd.now);
        proto.set_ecd(entity->Ecd.now);
        proto.set_rcd(entity->Rcd.now);
    }
}