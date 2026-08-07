#pragma once

#include <vector>
#include <functional>
#include "Signal.h"

// A callback function type that gates will register with the wire
using Action = std::function<void()>;

class Wire {
public:
    Wire();

    Signal getSignal() const;
    void setSignal(Signal new_state);
    void addAction(Action action);

private:
    Signal state;
    std::vector<Action> actions;
};