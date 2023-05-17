using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace View {
    public class ViewObject {
        public ulong id;
        public GameObject go;
        public GameObject bloodBar;
        public EntityProto.Types.ActionType action;
        public ViewObject(Model.Entity entity) {
            id = entity.id;
            go = Object.Instantiate(
                Tools.Loader.Prefab(Config.EntityPrefabStr(entity.type)));
            if (entity.type == EntityProto.Types.EntityType.Player ||
                Config.IsEnemy(entity.type)) {
                bloodBar = GameObject.Instantiate(Tools.Loader.Prefab("UI/BloodBar"), VCanvas.go.transform);
            }
        }

        public void Change(Model.Entity entity) {
            go.transform.position = new Vector3(entity.position.x, entity.height, entity.position.y);
            go.transform.rotation = Quaternion.Euler(0, entity.rotation * Mathf.Rad2Deg, 0);
            if (entity.action == EntityProto.Types.ActionType.Death) {
                Object.Destroy(bloodBar);
                bloodBar = null;
            }
            if (bloodBar != null) {
                bloodBar.transform.position = Camera.main.WorldToScreenPoint(go.transform.position + new Vector3(0, 2f, 1.7f));
                bloodBar.GetComponent<UnityEngine.UI.Slider>().value = entity.blood.now / entity.blood.max;
            }
            if (go.GetComponentInChildren<Animator>() != null && action != entity.action) {
                go.GetComponentInChildren<Animator>().Play(Config.AnimateString(entity));
                action = entity.action;
            }
        }

        public void Destroy() {
            Object.Destroy(go);
            if (bloodBar != null) {
                Object.Destroy(bloodBar);
            }
        }
    }
}