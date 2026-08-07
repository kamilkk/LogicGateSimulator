#include <vector>
#include <functional>
#include "Signal.h"

// A callback function type that gates will register with the wire
using Action = std::function<void()>;

class Wire {
public:
    Wire() : state(Signal::Unknown) {}

    Signal getSignal() const { return state; }
    
    void setSignal(Signal new_state) {
        if (state != new_state) {
            state = new_state;
            // Notify all connected gates that the signal changed
            for (auto& action : actions) {
                action();
            }
        }
    }

    // Allow a gate to register itself to be notified on state change
    void addAction(Action action) {
        actions.push_back(action);
        action(); // Trigger immediately to evaluate initial state
    }

private:
    Signal state;
    std::vector<Action> actions;
};