using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;
using UnityEngine;

public class Config {
    public const float CameraSpeed = 8f;
    public const float CameraMoveTiggerWidth = 20f;
    public static string host = "127.0.0.1";
    public static int port = 6688;

    public const float EPS = 0.0001f;

    public static void Awake() {
#if UNITY_EDITOR
        string configFile = Application.dataPath + "/config.txt";
#else
        string configFile = System.Environment.CurrentDirectory + "/config.txt";
#endif
        Debug.Log("config file: " + configFile);
        if (File.Exists(configFile)) {
            Debug.Log("load config");
            string[] lines = File.ReadAllLines(configFile);
            Regex regex_host = new(@"^host\b\s*[:=]\s*(\S*)$");
            Regex regex_port = new(@"^port\b\s*[:=]\s*(\S*)$");
            foreach (var s in lines) {
                {
                    var t = regex_host.Matches(s);
                    if (t.Count > 0) {
                        host = t[0].Groups[1].ToString();
                        Debug.Log("host = " + host);
                        continue;
                    }
                }
                {
                    var t = regex_port.Matches(s);
                    if (t.Count > 0) {
                        port = int.Parse(t[0].Groups[1].ToString());
                        Debug.Log("port = " + port);
                        continue;
                    }
                }
            }
        }
    }

    public static string AnimateString(Model.Entity entity) {
        if (entity.type == EntityProto.Types.EntityType.Player) {
            if (entity.action == EntityProto.Types.ActionType.Idle) {
                return "idle";
            } else if (entity.action == EntityProto.Types.ActionType.Move) {
                if (Model.Scene.working == false) {
                    return "run";
                }
                return "run";
            } else if (entity.action == EntityProto.Types.ActionType.Attack) {
                return Random.Range(0, 1) == 0 ? "attack_90" : "attack_180";
            } else if (entity.action == EntityProto.Types.ActionType.Attack1) {
                return Random.Range(0, 1) == 0 ? "attack_-90" : "attck_-180";
            } else if (entity.action == EntityProto.Types.ActionType.KaisaW) {
                return "skill_w";
            } else if (entity.action == EntityProto.Types.ActionType.KaisaE) {
                return "run";
            } else if (entity.action == EntityProto.Types.ActionType.KaisaR) {
                return "skill_r";
            }
        } else if (entity.type == EntityProto.Types.EntityType.Melee) {
            if (entity.action == EntityProto.Types.ActionType.Idle) {
                return "idle";
            } else if (entity.action == EntityProto.Types.ActionType.Move) {
                return "run";
            } else if (entity.action == EntityProto.Types.ActionType.MeleeAttack) {
                int t = Random.Range(0, 2);
                return t == 0 ? "attack" : t == 1 ? "attack2" : "attack3";
            } else if (entity.action == EntityProto.Types.ActionType.Death) {
                return "death";
            }
        } else if (entity.type == EntityProto.Types.EntityType.Nexus) {
            return "idle";
        } else if (entity.type == EntityProto.Types.EntityType.Satchel) {
            if (entity.action == EntityProto.Types.ActionType.Idle) {
                return "idle";
            } else if (entity.action == EntityProto.Types.ActionType.Invisible) {
                return "launch";
            }
        } else if (entity.type == EntityProto.Types.EntityType.Urgot) {
            if (entity.action == EntityProto.Types.ActionType.Idle) {
                return "idle";
            } else if (entity.action == EntityProto.Types.ActionType.Move) {
                return "run";
            } else if (entity.action == EntityProto.Types.ActionType.Attack) {
                return "attack";
            } else if (entity.action == EntityProto.Types.ActionType.Death) {
                return "death";
            }
        }
        Debug.LogError("no action:" + entity.type + " " + entity.action);
        return "";
    }

    public static string EntityPrefabStr(EntityProto.Types.EntityType type) {
        if (type == EntityProto.Types.EntityType.Player) {
            return "Kaisa/Prefab";
        } else if (type == EntityProto.Types.EntityType.Melee) {
            return "Melee/Prefab";
        } else if (type == EntityProto.Types.EntityType.Bullet) {
            return "Bullet";
        } else if (type == EntityProto.Types.EntityType.KaisaQbullet) {
            return "KaisaQBullet";
        } else if (type == EntityProto.Types.EntityType.KaisaWbullet) {
            return "KaisaWBullet";
        } else if (type == EntityProto.Types.EntityType.Nexus) {
            return "Nexus/Prefab";
        } else if (type == EntityProto.Types.EntityType.Satchel) {
            return "Satchel/Prefab";
        } else if (type == EntityProto.Types.EntityType.Urgot) {
            return "Urgot/Prefab";
        } else if (type == EntityProto.Types.EntityType.UrgotBullet) {
            return "UrgotBullet";
        }
        Debug.LogError("no prefab:" + type);
        return null;
    }

    public static bool IsEnemy(EntityProto.Types.EntityType type) {
        return type == EntityProto.Types.EntityType.Melee || type == EntityProto.Types.EntityType.Urgot;
    }
}
