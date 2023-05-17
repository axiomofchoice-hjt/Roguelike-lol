#pragma once

#include "tools/basic.h"

class Entity;
class Scene;

/// 敌人 AI
class EnemyAI {
   public:
    float sleep;
    shared<Entity> entity;
    Scene *scene;
    EnemyAI(shared<Entity> entity, Scene *scene);
    void run(float deltaTime);
};