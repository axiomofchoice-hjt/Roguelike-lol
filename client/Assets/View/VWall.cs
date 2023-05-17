using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace View {
    public class VWall {
        const float Length = 3f;
        const float Thickness = 0.3f;

        public ulong id;
        public List<GameObject> gos;
        public VWall(Model.Wall wall) {
            id = wall.id;
            gos = new();
            var p1 = wall.p1;
            var p2 = wall.p2;
            if (p1.x == p2.x) {
                for (float i = p1.y + Length / 2; i < p2.y; i += Length) {
                    var go = Object.Instantiate(Tools.Loader.Prefab("Wall"));
                    go.transform.position = new Vector3(p1.x, wall.height, i);
                    go.transform.localScale = new Vector3(Thickness, Length, Length);
                    gos.Add(go);
                }
            } else if (p1.y == p2.y) {
                for (float i = p1.x + Length / 2; i < p2.x; i += Length) {
                    var go = Object.Instantiate(Tools.Loader.Prefab("Wall"));
                    go.transform.position = new Vector3(i, wall.height, p1.y);
                    go.transform.localScale = new Vector3(Length, Length, Thickness);
                    gos.Add(go);
                }
            } else {
                Debug.LogError("VWall error");
            }
        }

        public void Change(Model.Wall wall) {
            foreach (var go in gos) {
                go.transform.position = new Vector3(go.transform.position.x, wall.height, go.transform.position.z);
            }
        }

        public void Remove() {
            foreach (var go in gos) {
                Object.Destroy(go);
            }
        }
    }
}