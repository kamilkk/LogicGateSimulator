#include "Wire.h"

Wire::Wire() : state(Signal::Unknown) {}

Signal Wire::getSignal() const {
    return state;
}

void Wire::setSignal(Signal new_state) {
    if (state != new_state) {
        state = new_state;
        // Notify all connected gates that the signal changed
        for (auto& action : actions) {
            action();
        }
    }
}

void Wire::addAction(Action action) {
    actions.push_back(action);
    action(); // Trigger immediately to evaluate initial state
}