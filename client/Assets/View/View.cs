using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

namespace View {
    public class Scene {
        public static ViewObject player;
        public static List<ViewObject> list;
        public static List<VWall> vwalls;

        public static void Awake() {
            list = new();
            vwalls = new();
        }

        public static ViewObject Find(ulong id) {
            foreach (ViewObject i in list) {
                if (i.id == id) {
                    return i;
                }
            }
            return null;
        }
        public static VWall FindVWall(ulong id) {
            foreach (VWall i in vwalls) {
                if (i.id == id) {
                    return i;
                }
            }
            return null;
        }

        public static void Update() {
            { // 处理 entities
                List<ViewObject> nextList = new();
                foreach (Model.Entity entity in Model.Scene.entities) {
                    var vo = Find(entity.id);
                    if (vo != null) {
                        vo.Change(entity);
                        nextList.Add(vo);
                        list.Remove(vo);
                    } else {
                        vo = new(entity);
                        vo.go.transform.localScale = Vector3.one * 1.3f;
                        vo.Change(entity);
                        nextList.Add(vo);
                    }
                }
                foreach (ViewObject vo in list) {
                    vo.Destroy();
                }
                list = nextList;
            }
            { // 处理 walls
                List<VWall> nextList = new();
                foreach (Model.Wall wall in Model.Scene.walls) {
                    var vw = FindVWall(wall.id);
                    if (vw != null) {
                        vw.Change(wall);
                        nextList.Add(vw);
                        vwalls.Remove(vw);
                    } else {
                        vw = new(wall);
                        vw.Change(wall);
                        nextList.Add(vw);
                    }
                }
                foreach (var vw in vwalls) {
                    vw.Remove();
                }
                vwalls = nextList;
            }
            player = Find(Model.Scene.selfId);
        }
    }
}