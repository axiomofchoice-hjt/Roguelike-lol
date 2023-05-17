using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Main : MonoBehaviour {
    private void Awake() {
        Application.targetFrameRate = 60;
        Tools.Loader.Awake();
        Config.Awake();
        Model.Scene.Awake();
        Model.MCamera.Awake();
        View.Scene.Awake();
        View.ChunkControl.Awake();
    }

    private void Start() {
        Tools.Remote.Start();
        Model.InputControl.Start();
        View.VCamera.Start();
        View.VCanvas.Start();
        View.AttackRadius.Start();
        View.Skills.Start();
        View.VKaisaWIndicator.Start();
    }

    private void Update() {
        float deltaTime = Time.deltaTime;

        // Before
        Model.InputControl.UpdateBefore();

        // Model
        Model.Scene.Update(deltaTime);
        Model.InputControl.Update(deltaTime);

        // View (after Model)
        View.VCamera.Update();
        View.Scene.Update();
        View.AttackRadius.Update();
        View.Skills.Update();
        View.VKaisaWIndicator.Update();
        View.ChunkControl.Update();
    }

    private void OnDestroy() {
        Tools.Remote.Destroy();
    }
}
