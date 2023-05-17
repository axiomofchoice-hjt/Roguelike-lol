using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace View {
    public class Chunk {
        public static float size = 40f;
        public List<GameObject> gos;
        public (long x, long y) position;

        static GameObject rand_go(string s, System.Random rand, long x, long y) {
            var go = Object.Instantiate(Tools.Loader.Prefab(s));
            go.transform.position = new Vector3(((float)rand.NextDouble() + x - 0.5f) * size,
                                                0,
                                                ((float)rand.NextDouble() + y - 0.5f) * size);
            go.transform.localScale = new Vector3(2, 2, 2);
            go.transform.rotation = Quaternion.Euler(0, (float)rand.NextDouble() * 360, 0);
            return go;
        }

        public Chunk(long x, long y) {
            this.position = (x, y);
            gos = new();
            var rand = new System.Random((int)(
                    (uint)Model.Scene.world_seed + (uint)(
                    (x * x) * 0x4C1906 + (x * 0x5AC0DB) +
                    (y * y) * 0x4307A7 + (y * 0x5F24F) ^ 0x3AD8025F)
                )
            );
            {
                var floor = Object.Instantiate(Tools.Loader.Prefab("Floor"));

                floor.transform.position = new Vector3(x * size, 0, y * size);
                floor.transform.localScale = new Vector3(size / 10, 1, size / 10);
                gos.Add(floor);
            }
            for (int i = rand.Next(20, 40); i != 0; i--) {
                gos.Add(Chunk.rand_go("LowPolyEnvironment/Prefabs/Grass_2", rand, x, y));
            }
            for (int i = rand.Next(3, 5); i != 0; i--) {
                gos.Add(Chunk.rand_go("LowPolyEnvironment/Prefabs/Stone_1", rand, x, y));
            }
        }

        public void Remove() {
            foreach (var go in gos) {
                Object.Destroy(go);
            }
        }
    }
}