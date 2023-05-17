using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Model {
    public class MCamera {
        public static Vector2 position;
        public static float height;
        public static float angle;

        public static void Awake() {
            position = Vector2.zero;
            height = 20;
            angle = 70;
        }

        public static void Follow() {
            if (Input.GetKey(KeyCode.Space) || Events.lock_camera) {
                MCamera.position = Scene.player.position;
            }
        }

        public static void Move(float deltaTime) {
            Vector2 delta = new();
            if (Mathf.Abs(InputControl.mouseUi.x) <= Config.CameraMoveTiggerWidth) {
                delta.x -= height * 0.5f * deltaTime;
            }
            if (Mathf.Abs(InputControl.mouseUi.x - Screen.width) <= Config.CameraMoveTiggerWidth) {
                delta.x += height * 0.5f * deltaTime;
            }
            if (Mathf.Abs(InputControl.mouseUi.y) <= Config.CameraMoveTiggerWidth) {
                delta.y -= height * 0.5f * deltaTime;
            }
            if (Mathf.Abs(InputControl.mouseUi.y - Screen.height) <= Config.CameraMoveTiggerWidth) {
                delta.y += height * 0.5f * deltaTime;
            }
            MCamera.position += delta;
        }

        public static void Lift(float deltaTime) {
            if (Scene.working) {
                height -= deltaTime * 20;
                height = Mathf.Max(height, 20);
            } else {
                height += deltaTime * 20;
                height = Mathf.Min(height, 40);
            }
        }

        public static void Update(float deltaTime) {
            MCamera.Move(deltaTime);
            MCamera.Follow();
            MCamera.Lift(deltaTime);
        }
    }
}