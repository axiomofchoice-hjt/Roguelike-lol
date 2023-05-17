using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace View {
    public class ChunkControl {
        static public List<Chunk> chunks;

        static public void Awake() {
            chunks = new();
        }

        static private (long x, long y) WhichChunk(Vector2 v) {
            return (Mathf.RoundToInt(v.x / Chunk.size), Mathf.RoundToInt(v.y / Chunk.size));
        }

        static private long Abs(long x) {
            return x >= 0 ? x : -x;
        }

        static private bool Find((long, long) pos) {
            foreach (var chunk in chunks) {
                if (chunk.position == pos) {
                    return true;
                }
            }
            return false;
        }

        static public void Update() {
            var camera = ChunkControl.WhichChunk(Model.MCamera.position);
            for (int i = chunks.Count - 1; i >= 0; i--) {
                if (Abs(chunks[i].position.x - camera.x) > 3 || Abs(chunks[i].position.y - camera.y) > 2) {
                    chunks[i].Remove();
                    chunks.RemoveAt(i);
                }
            }

            for (int i = -2; i <= 2; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (!Find((camera.x + i, camera.y + j))) {
                        chunks.Add(new Chunk(camera.x + i, camera.y + j));
                    }
                }
            }
        }
    }
}