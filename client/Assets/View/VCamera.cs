using Model;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace View {
    public class VCamera {
        public static GameObject go;
        public static float k;

        public static void Start() {
            go = GameObject.Find("Main Camera");
            Debug.Assert(MCamera.angle > 0 && MCamera.angle <= 90);
            k = Mathf.Tan(Mathf.Deg2Rad * (90 - MCamera.angle));
            go.transform.rotation = Quaternion.Euler(MCamera.angle, 0, 0);
            Update();
        }

        public static void Update() {
            Debug.Assert(MCamera.height > 0);

            go.transform.position = new Vector3(
                MCamera.position.x,
                MCamera.height,
                MCamera.position.y - MCamera.height * k
            );
        }
    }
}