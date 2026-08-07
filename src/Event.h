#pragma once

#include <memory>
#include "Wire.h"

struct Event {
    uint64_t time;
    std::shared_ptr<Wire> target_wire;
    Signal new_signal;
    uint64_t id;

    bool operator>(const Event& other) const {
        if (time != other.time) return time > other.time;
        return id > other.id;
    }
};