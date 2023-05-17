using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static UnityEngine.EventSystems.EventTrigger;

namespace Model {
    public class Scene {
        public static SceneProto proto;
        public static bool ok;
        public static ulong world_seed;
        public static ulong selfId;
        public static Entity player;
        public static List<Entity> entities;
        public static List<Wall> walls;
        public static float attack_radius = 1;
        public static float Acd;
        public static float Qcd;
        public static float Wcd;
        public static float Ecd;
        public static float Rcd;
        public static bool working;

        public static Entity Find(ulong id) {
            foreach (var i in entities) {
                if (i.id == id) {
                    return i;
                }
            }
            throw new("Model.Scene.Find error");
        }

        public static void Awake() {
            entities = new();
            walls = new();
            ok = false;
        }

        public static void Parse() {
            world_seed = proto.WorldSeed;
            selfId = proto.Id;
            entities.Clear();
            foreach (EntityProto e_proto in proto.Entities) {
                entities.Add(Entity.Parse(e_proto));
            }
            walls.Clear();
            foreach (WallProto w_proto in proto.Walls) {
                walls.Add(Wall.Parse(w_proto));
            }
            working = proto.Working;

            attack_radius = proto.AttackRadius;
            Acd = proto.Acd;
            Qcd = proto.Qcd;
            Wcd = proto.Wcd;
            Ecd = proto.Ecd;
            Rcd = proto.Rcd;
            player = Find(selfId);
        }

        public static void Update(float deltaTime) {
            if (proto != null) {
                Parse();
                proto = null;
                ok = true;
            } else {
                Simulate(deltaTime);
            }
        }

        public static void Simulate(float deltaTime) {
            foreach (var entity in entities) {
                entity.position += new Vector2(entity.velocity.x, entity.velocity.z) * deltaTime;
                entity.height += entity.velocity.y * deltaTime;
            }
        }
    }
}