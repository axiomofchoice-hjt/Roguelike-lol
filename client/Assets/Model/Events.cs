using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Model {
    public class Events : MonoBehaviour {
        public static GameObject PauseView;
        public static GameObject PauseButton;
        public static GameObject ConnectFail;
        public static bool pause;
        public static bool lock_camera;
        public static bool quick_attack;

        void Awake() {
            pause = false;
            lock_camera = false;
            quick_attack = false;
        }

        void Start() {
            PauseView = GameObject.Find("PauseView");
            PauseButton = GameObject.Find("PauseButton");
            ConnectFail = GameObject.Find("ConnectFail");
            PauseView.SetActive(pause);
            ConnectFail.SetActive(false);
            PauseButton.transform.SetAsLastSibling();
        }

        public void Pause() {
            pause ^= true;
            PauseView.SetActive(pause);
            UnityEngine.EventSystems.EventSystem.current.SetSelectedGameObject(null);
        }

        public void LockCamera() {
            lock_camera ^= true;
        }

        public void QuickAttack() {
            quick_attack ^= true;
        }

        public void Exit() {
#if UNITY_EDITOR
            UnityEditor.EditorApplication.isPlaying = false;
#else
        Application.Quit();
#endif
        }
    }
}