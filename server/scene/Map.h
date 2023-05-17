#pragma once

#include "tools/Vector.h"
#include "tools/basic.h"

class Entity;
class Scene;
namespace wall {
class Wall;
}

namespace map {
class Room {
   public:
    enum class State {
        Invisible,
        Ready,
        Working,
        Finished,
    };
    bool is_invisible() const { return state == State::Invisible; }
    bool is_ready() const { return state == State::Ready; }
    bool is_working() const { return state == State::Working; }
    bool is_finished() const { return state == State::Finished; }
    State state;
    shared<Entity> satchel;
    int x;
    int y;
    bool is_final;  // 是否是最终房间
    Room(int, int, Scene *);
    bool in_area(vec2 position) const;
    void block_player(Entity &entity) const;
};

class RoomWall {
   public:
    shared<wall::Wall> midwall;
    shared<wall::Wall> extwall1;
    shared<wall::Wall> extwall2;
    shared<Room> room1;
    shared<Room> room2;
    RoomWall(shared<Room> a, shared<Room> b, Scene *);
    RoomWall(shared<Room> a, int bx, int by, Scene *);
    bool is_split() const { return room2 != nullptr; }
};

class Map {
   public:
    std::vector<shared<Room>> rooms;
    std::vector<shared<RoomWall>> room_walls;
    shared<Entity> nexus;
    shared<Room> working_room;
    Scene *scene;

    Map(Scene *);
    shared<Room> find_room_by_satchel(u64 id) const;
    shared<Room> find_room_by_xy(int x, int y) const;
    void set_working(u64 id);
    void set_ok();
    void on_change();
    void block_player(Entity &entity) const;
};
}  // namespace map
