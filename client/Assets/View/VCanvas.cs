using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace View {
    public class VCanvas {
        public static GameObject go;

        public static void Start() {
            go = GameObject.Find("Canvas");
        }
    }
}