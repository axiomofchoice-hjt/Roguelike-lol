using Google.Protobuf.Collections;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace View {
    public class AttackRadius {
        private const int SEGMENT = 100;
        static float now_attack_radius = 0;

        static GameObject go;
        static LineRenderer lines;

        public static void Start() {
            go = Object.Instantiate(Tools.Loader.Prefab("Line"));
            lines = go.GetComponent<LineRenderer>();

            lines.enabled = false;
            lines.positionCount = SEGMENT;
            lines.loop = true;
            lines.startWidth = 0.05f;
            lines.endWidth = 0.05f;
        }

        public static void Update() {
            if (Model.Scene.attack_radius != now_attack_radius) {
                now_attack_radius = Model.Scene.attack_radius;
                for (int i = 0; i < SEGMENT; i++) {
                    lines.SetPosition(
                        i,
                        new Vector3(
                            Mathf.Cos(Mathf.PI * 2 * i / SEGMENT) * now_attack_radius,
                            0.05f,
                            Mathf.Sin(Mathf.PI * 2 * i / SEGMENT) * now_attack_radius
                        )
                    );
                }
            }

            var self = Scene.player;
            if (self != null && Model.InputControl.pressA) {
                go.transform.position = self.go.transform.position;
                lines.enabled = true;
            } else {
                lines.enabled = false;
            }
        }
    }
}