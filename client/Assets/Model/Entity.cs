using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Model {

    public class Entity {
        public ulong id;
        public Vector2 position;
        public float height;
        public Vector3 velocity;
        public float rotation;
        public (float now, float max) blood;
        public EntityProto.Types.EntityType type;
        public EntityProto.Types.ActionType action;

        static public Entity Parse(EntityProto proto) {
            Entity entity = new() {
                id = proto.Id,
                position = new Vector2(proto.Position.X, proto.Position.Z),
                height = proto.Position.Y,
                velocity = new Vector3(proto.Velocity.X, proto.Velocity.Y, proto.Velocity.Z),
                rotation = proto.Rotation,
                blood = (proto.Blood.Now, proto.Blood.Max),
                type = proto.Type,
                action = proto.Action,
            };
            return entity;
        }
    }
}