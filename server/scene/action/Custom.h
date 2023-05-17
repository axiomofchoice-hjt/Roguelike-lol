#pragma once

#include <functional>

#include "Action.h"

class Scene;

namespace action {
/// 自定义动作
class Custom : public Action {
   public:
    std::function<bool(float &)> func;
    Custom(const std::function<bool(float &)> &func)
        : Action(nullptr), func(func) {}
    bool run(float &deltaTime) override;
};
}  // namespace action