using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

namespace View {
    public class Skills {
        static GameObject Q;
        static GameObject W;
        static GameObject E;
        static GameObject R;
        static GameObject QCD;
        static GameObject WCD;
        static GameObject ECD;
        static GameObject RCD;

        public static void Start() {
            Q = GameObject.Find("SkillQ");
            W = GameObject.Find("SkillW");
            E = GameObject.Find("SkillE");
            R = GameObject.Find("SkillR");
            QCD = GameObject.Find("QCD");
            WCD = GameObject.Find("WCD");
            ECD = GameObject.Find("ECD");
            RCD = GameObject.Find("RCD");
        }

        static void SetCDText(GameObject go, float cd) {
            if (cd < Config.EPS) {
                go.GetComponent<TextMeshProUGUI>().text = "";
            } else {
                go.GetComponent<TextMeshProUGUI>().text = cd.ToString("#0.0");
            }
        }

        static void SetColor(GameObject go, float cd) {
            if (cd < Config.EPS) {
                go.GetComponent<Image>().color = new Color(1, 1, 1, 1f);
            } else {
                go.GetComponent<Image>().color = new Color(1, 1, 1, 0.3f);
            }
        }

        public static void Update() {
            SetColor(Q,    Model.Scene.Qcd);
            SetColor(W,    Model.Scene.Wcd);
            SetColor(E,    Model.Scene.Ecd);
            SetColor(R,    Model.Scene.Rcd);
            SetCDText(QCD, Model.Scene.Qcd);
            SetCDText(WCD, Model.Scene.Wcd);
            SetCDText(ECD, Model.Scene.Ecd);
            SetCDText(RCD, Model.Scene.Rcd);
        }
    }
}