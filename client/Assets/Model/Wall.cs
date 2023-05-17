using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Model {
    public class Wall {
        public ulong id;
        public Vector2 p1;
        public Vector2 p2;
        public float height;
        static public Wall Parse(WallProto proto) {
            Wall wall = new() {
                id = proto.Id,
                p1 = new Vector2(proto.P1.X, proto.P1.Y),
                p2 = new Vector2(proto.P2.X, proto.P2.Y),
                height = proto.Height,
            };
            return wall;
        }
    }
}
