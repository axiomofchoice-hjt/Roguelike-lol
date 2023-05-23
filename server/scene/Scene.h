#pragma once

#include <memory>
#include <vector>

#include "Entity.h"
#include "Map.h"
#include "proto/Message.pb.h"
#include "proto/Scene.pb.h"
#include "scene/Wall.h"
#include "tools/basic.h"

class SocketConn;

/// 场景
class Scene {
   public:
    u64 world_seed = 0;
    std::vector<shared<Entity>> entities;
    std::vector<shared<Entity>> add_entities;

    std::vector<shared<wall::Wall>> walls;

    uptr<map::Map> map;
    /// 场上几个怪
    u64 enemy_count;
    /// 运行了几个逻辑帧
    u64 update_count;
    /// 是否完成
    bool finished;

    Scene();
    void init();
    shared<Entity> add_entity(u64 id, EntityProto::EntityType type);
    shared<Entity> find(u64 id) const;
    shared<wall::Wall> find_wall(u64 id);
    void receive(SocketConn &conn, const MessageProto &msg);
    void update(float deltaTime);

    void print() const;

    SceneProto proto() const;
    void others_to_proto(SceneProto &proto, u64 id) const;
};