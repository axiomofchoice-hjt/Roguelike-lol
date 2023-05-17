using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace View {
    public class VKaisaWIndicator {
        static GameObject go;
        static LineRenderer lines;
        public static void Start() {
            go = Object.Instantiate(Tools.Loader.Prefab("Line"));
            lines = go.GetComponent<LineRenderer>();

            lines.enabled = false;
            lines.positionCount = 2;
            lines.startWidth = 0.05f;
            lines.endWidth = 0.05f;
            lines.SetPosition(0, new Vector3(0, 0, 0));
            lines.SetPosition(1, new Vector3(0, 0, 18));
        }

        public static void Update() {
            var self = Model.Scene.player;
            if (self != null && Model.InputControl.pressW) {
                var delta = Model.InputControl.mouse - self.position;
                go.transform.position = new Vector3(self.position.x, 0, self.position.y);
                go.transform.rotation = Quaternion.Euler(0, Mathf.Atan2(delta.x, delta.y) * Mathf.Rad2Deg, 0);
                lines.enabled = true;
            } else {
                lines.enabled = false;
            }
        }
    }
}