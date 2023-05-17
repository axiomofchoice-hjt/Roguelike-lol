#include "Action.h"

#include <iostream>

namespace action {

void ActionList::clear() { data.clear(); }
bool ActionList::empty() const { return data.empty(); }

void ActionList::run(float deltaTime) {
    while (!empty()) {
        bool ok = data.front()->run(deltaTime);
        if (ok) {
            data.pop_front();
        } else {
            break;
        }
    }
    if (empty()) {
        type = EntityProto_ActionType_Undefined;
    }
}
}  // namespace action