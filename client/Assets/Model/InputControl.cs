using Google.Protobuf;
using System;
using UnityEngine;
using static EntityProto.Types;

namespace Model {
    public class InputControl {
        public static bool pressA;
        public static bool pressW;
        public static Vector2 mouse;
        public static Vector2 mouseUi;

        public static void Start() {
            pressA = false;
        }

        static ulong NearestEnemy(Vector2 pos) {
            Entity select = null;
            foreach (Entity entity in Scene.entities) { // 找最近的敌人
                if ((Config.IsEnemy(entity.type)
                    || entity.type == EntityType.Satchel
                    || entity.type == EntityType.Nexus)
                    && entity.action != ActionType.Death
                    && entity.action != ActionType.Invisible) {
                    if (select == null ||
                        Vector2.Distance(pos, select.position) > Vector2.Distance(pos, entity.position)) {
                        select = entity;
                    }
                }
            }
            if (select != null) {
                return select.id;
            } else {
                return ulong.MaxValue;
            }
        }

        static MessageProto GenMessage(MessageProto.Types.Type type) {
            return new() {
                Position = new() {
                    X = mouse.x,
                    Y = mouse.y,
                },
                Target = NearestEnemy(mouse),
                Type = type
            };
        }

        static void Move() {
            if (Input.GetMouseButtonDown(1)) { // right button
                pressA = false;
                MessageProto proto =
                    GenMessage(MessageProto.Types.Type.Move);
                Tools.Remote.Send(proto.ToByteArray());
            }
        }

        static void Attack() {
            if (Events.quick_attack) {
                if (!pressW && Input.GetKeyDown(KeyCode.A)) {
                    pressA = true;
                    MessageProto proto = new() {
                        Position = new() {
                            X = mouse.x,
                            Y = mouse.y,
                        },
                        Target = NearestEnemy(Scene.player.position),
                        Type = MessageProto.Types.Type.Attack
                    };
                    Tools.Remote.Send(proto.ToByteArray());
                }
            } else {
                if (!pressW && Input.GetKeyDown(KeyCode.A)) {
                    pressA = true;
                }
                if (Input.GetMouseButtonDown(0) && pressA) { // left button && pressA
                    pressA = false;
                    MessageProto proto =
                        GenMessage(MessageProto.Types.Type.Attack);
                    Tools.Remote.Send(proto.ToByteArray());
                }
            }
        }

        static void Test() {
            if (Input.GetKeyDown(KeyCode.T)) {
                MessageProto proto =
                    GenMessage(MessageProto.Types.Type.Test);
                Tools.Remote.Send(proto.ToByteArray());
            }
            if (Input.GetKeyDown(KeyCode.C)) {
                MessageProto proto =
                    GenMessage(MessageProto.Types.Type.ClearEnemies);
                Tools.Remote.Send(proto.ToByteArray());
            }
        }

        static void Skill() {
            // Q
            if (Input.GetKeyDown(KeyCode.Q) && Scene.Qcd == 0) {
                pressA = false;
                pressW = false;
                MessageProto proto =
                    GenMessage(MessageProto.Types.Type.Q);
                Tools.Remote.Send(proto.ToByteArray());
            }
            // W
            if (Input.GetKeyDown(KeyCode.W) && Scene.Wcd == 0) {
                pressA = false;
                pressW = true;
            }
            if (Input.GetKeyUp(KeyCode.W) && pressW) {
                pressW = false;
                if (Scene.Wcd == 0) {
                    MessageProto proto =
                        GenMessage(MessageProto.Types.Type.W);
                    Tools.Remote.Send(proto.ToByteArray());
                }
            }
            // E
            if (Input.GetKeyDown(KeyCode.E) && Scene.Ecd == 0) {
                MessageProto proto =
                    GenMessage(MessageProto.Types.Type.E);
                Tools.Remote.Send(proto.ToByteArray());
            }
            // R
            if (Input.GetKeyDown(KeyCode.R) && Scene.Rcd == 0) {
                MessageProto proto =
                GenMessage(MessageProto.Types.Type.R);
                Tools.Remote.Send(proto.ToByteArray());
            }
        }

        public static void UpdateBefore() {
            // set mouse
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            Debug.Assert(ray.origin.y > 0);
            Debug.Assert(ray.direction.y < 0);
            mouse = new Vector2(
                 ray.origin.x + Mathf.Abs(ray.origin.y / ray.direction.y) * ray.direction.x,
                 ray.origin.z + Mathf.Abs(ray.origin.y / ray.direction.y) * ray.direction.z
            );
            mouseUi = new(Input.mousePosition.x, Input.mousePosition.y);
        }

        public static void Update(float deltaTime) {
            Move();
            Attack();
            Test();
            Skill();
            MCamera.Update(deltaTime);
        }
    }
}