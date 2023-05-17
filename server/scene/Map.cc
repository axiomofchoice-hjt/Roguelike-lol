#include "Map.h"

#include "Config.h"
#include "Entity.h"
#include "Scene.h"
#include "action/comb.h"
#include "tools/UUID.h"

namespace map {
static int dx[] = {0, 0, 1, -1};
static int dy[] = {1, -1, 0, 0};
Room::Room(int x, int y, Scene *scene)
    : state(State::Invisible), x(x), y(y), is_final() {
    satchel = scene->add_entity(UUID::get(), EntityProto_EntityType_Satchel);
    satchel->action = action::comb::Invisible(satchel);
    *satchel->position = vec2(Config::room_size() * (x + Rand::f(-0.45, 0.45)),
                              Config::room_size() * (y + Rand::f(-0.45, 0.45)));
    satchel->blood.now = 1;
}

bool Room::in_area(vec2 position) const {
    position /= Config::room_size();
    return x - 0.5 <= position.x && position.x <= x + 0.5 &&
           y - 0.5 <= position.y && position.y <= y + 0.5;
}

void Room::block_player(Entity &entity) const {
    bool flag = false;
    if (entity.position->x <
        Config::room_size() * (x - 0.5f) + entity.collide_radius) {
        entity.position->x =
            Config::room_size() * (x - 0.5f) + entity.collide_radius;
        flag = true;
    }
    if (entity.position->x >
        Config::room_size() * (x + 0.5f) - entity.collide_radius) {
        entity.position->x =
            Config::room_size() * (x + 0.5f) - entity.collide_radius;
        flag = true;
    }
    if (entity.position->y <
        Config::room_size() * (y - 0.5f) + entity.collide_radius) {
        entity.position->y =
            Config::room_size() * (y - 0.5f) + entity.collide_radius;
        flag = true;
    }
    if (entity.position->y >
        Config::room_size() * (y + 0.5f) - entity.collide_radius) {
        entity.position->y =
            Config::room_size() * (y + 0.5f) - entity.collide_radius;
        flag = true;
    }
    if (flag) {
        entity.move_to = nullptr;
    }
}

RoomWall::RoomWall(shared<Room> a, shared<Room> b, Scene *scene) {
    vec2 A, B;
    if (a->x == b->x) {
        A = vec2(a->x - 0.5f, (a->y + b->y) / 2.f) * Config::room_size();
        B = vec2(a->x + 0.5f, (a->y + b->y) / 2.f) * Config::room_size();
    } else {
        A = vec2((a->x + b->x) / 2.f, a->y - 0.5f) * Config::room_size();
        B = vec2((a->x + b->x) / 2.f, a->y + 0.5f) * Config::room_size();
    }
    vec2 AAB = (A * 0.7 + B * 0.3);
    vec2 ABB = (A * 0.3 + B * 0.7);
    auto wall1 = std::make_shared<wall::Wall>(A, AAB);
    auto wall2 = std::make_shared<wall::Wall>(AAB, ABB);
    auto wall3 = std::make_shared<wall::Wall>(ABB, B);
    scene->walls.push_back(wall1);
    scene->walls.push_back(wall2);
    scene->walls.push_back(wall3);
    midwall = wall2;
    extwall1 = wall1;
    extwall2 = wall3;
    room1 = a;
    room2 = b;
}

RoomWall::RoomWall(shared<Room> a, int bx, int by, Scene *scene) {
    vec2 A, B;
    if (a->x == bx) {
        A = vec2(a->x - 0.5f, (a->y + by) / 2.f) * Config::room_size();
        B = vec2(a->x + 0.5f, (a->y + by) / 2.f) * Config::room_size();
    } else {
        A = vec2((a->x + bx) / 2.f, a->y - 0.5f) * Config::room_size();
        B = vec2((a->x + bx) / 2.f, a->y + 0.5f) * Config::room_size();
    }
    auto wall = std::make_shared<wall::Wall>(A, B);
    scene->walls.push_back(wall);
    midwall = wall;
    extwall1 = nullptr;
    extwall2 = nullptr;
    room1 = a;
    room2 = nullptr;
}

Map::Map(Scene *scene) : working_room(), scene(scene) {
    // 生成房间
    rooms.push_back(std::make_shared<Room>(0, 0, scene));
    for (int i = 1; i <= 3; i++) {
        int x, y;
        while (true) {
            int t = Rand::d(4);
            auto room = rooms[Rand::d(i)];
            x = room->x + dx[t];
            y = room->y + dy[t];
            if (find_room_by_xy(x, y) == nullptr) {
                break;
            }
        }
        rooms.push_back(std::make_shared<Room>(x, y, scene));
    }
    rooms.back()->is_final = true;

    // 生成水晶
    {
        nexus = scene->add_entity(UUID::get(), EntityProto_EntityType_Nexus);
        *nexus->position =
            vec2(Config::room_size() * (rooms.back()->x + Rand::f(-0.2, 0.2)),
                 Config::room_size() * (rooms.back()->y + Rand::f(-0.2, 0.2)));
        nexus->blood.now = 1;
        nexus->action = action::comb::Invisible(nexus);
    }

    // 生成墙
    for (auto &room : rooms) {
        for (int i = 0; i < 4; i++) {
            if (!find_room_by_xy(room->x + dx[i], room->y + dy[i])) {
                room_walls.push_back(std::make_shared<RoomWall>(
                    room, room->x + dx[i], room->y + dy[i], scene));
            }
        }
        auto to = find_room_by_xy(room->x + 1, room->y);
        if (to) {
            room_walls.push_back(std::make_shared<RoomWall>(room, to, scene));
        }
        to = find_room_by_xy(room->x, room->y + 1);
        if (to) {
            room_walls.push_back(std::make_shared<RoomWall>(room, to, scene));
        }
    }
    rooms[0]->state = Room::State::Ready;
    on_change();
}

void Map::on_change() {
    for (auto &rwall : room_walls) {
        if (!rwall->is_split()) {
            if (rwall->room1->is_invisible()) {
                rwall->midwall->activate = false;
            } else {
                rwall->midwall->activate = true;
            }
        }
        if (rwall->is_split()) {
            if (rwall->room1->is_invisible() && rwall->room2->is_invisible()) {
                rwall->midwall->activate = false;
                rwall->extwall1->activate = false;
                rwall->extwall2->activate = false;
            } else if (rwall->room1->is_invisible() ||
                       rwall->room2->is_invisible()) {
                rwall->midwall->activate = true;
                rwall->extwall1->activate = true;
                rwall->extwall2->activate = true;
            } else if (working_room) {
                rwall->midwall->activate = true;
                rwall->extwall1->activate = true;
                rwall->extwall2->activate = true;
            } else {
                rwall->midwall->activate = false;
                rwall->extwall1->activate = true;
                rwall->extwall2->activate = true;
            }
        }
    }
    for (auto &i : rooms) {
        if (!working_room && i->state == Room::State::Ready) {
            i->satchel->action = action::comb::Idle();
        } else {
            i->satchel->action = action::comb::Invisible(i->satchel);
        }
    }
}

shared<Room> Map::find_room_by_satchel(u64 id) const {
    for (auto &room : rooms) {
        if (room->satchel->id == id) {
            return room;
        }
    }
    return nullptr;
}

shared<Room> Map::find_room_by_xy(int x, int y) const {
    for (auto &room : rooms) {
        if (room->x == x && room->y == y) {
            return room;
        }
    }
    return nullptr;
}

void Map::set_working(u64 id) {
    log_info("set working id={}", id);
    working_room = find_room_by_satchel(id);
    working_room->state = Room::State::Working;
    on_change();
}

void Map::set_ok() {
    working_room = nullptr;
    shared<Room> room_ptr = nullptr;
    for (auto &room : rooms) {
        if (room->state == Room::State::Working) {
            room_ptr = room;
            break;
        }
    }
    room_ptr->state = Room::State::Finished;
    if (room_ptr->is_final) {
        nexus->action = action::comb::Idle();
    }
    log_info("set ok id={}", room_ptr->satchel->id);
    for (int d = 0; d < 4; d++) {
        int x = room_ptr->x + dx[d];
        int y = room_ptr->y + dy[d];
        auto to = find_room_by_xy(x, y);
        if (to && to->is_invisible()) {
            to->state = Room::State::Ready;
        }
    }
    on_change();
}

void Map::block_player(Entity &entity) const {
    if (working_room) {
        working_room->block_player(entity);
    } else {
        vec2 pos = *entity.position / Config::room_size();
        shared<Room> nearest_room;
        for (const auto &i : rooms) {
            if (!i->is_invisible() &&
                (nearest_room == nullptr ||
                 geo::distance(pos, vec2(i->x, i->y)) <
                     geo::distance(pos,
                                   vec2(nearest_room->x, nearest_room->y)))) {
                nearest_room = i;
            }
        }
        if (!nearest_room->in_area(*entity.position)) {
            nearest_room->block_player(entity);
        }
    }
}
}  // namespace map