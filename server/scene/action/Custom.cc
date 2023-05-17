#include "Custom.h"

namespace action {
bool Custom::run(float &deltaTime) { return func(deltaTime); }
}  // namespace action