using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace View {
    public class Env {
        public GameObject go;
        // public Env(EnvProto proto) {
        //     go = Object.Instantiate(Tools.Loader.Prefab(Config.EnvPrefabStr(proto.Type)));
        //     go.transform.position = new Vector3(proto.Position.X,
        //                                         proto.Position.Y,
        //                                         proto.Position.Z);
        //     go.transform.localScale = new Vector3(proto.Scale.X,
        //                                           proto.Scale.Y,
        //                                           proto.Scale.Z);
        //     go.transform.rotation = Quaternion.Euler(0, proto.Rotation, 0);
        // }
        public void Remove() {
            Object.Destroy(go);
        }
    }
}