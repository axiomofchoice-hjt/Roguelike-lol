using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

namespace Tools {
    public class Loader {
        static Dictionary<string, Object> table;

        public static void Awake() {
            table = new();
        }

        public static Object Get(string key) {
            if (key == null) {
                Debug.LogError("Loader.Get: key is null");
                return null;
            }
            if (table.ContainsKey(key)) {
                return table[key];
            } else {
                Object ret = Resources.Load(key);
                table[key] = ret;
                return ret;
            }
        }

        public static GameObject Prefab(string key) {
            return (GameObject)Get(key);
        }

        public static Material Mater(string key) {
            return (Material)Get(key);
        }
    }
}