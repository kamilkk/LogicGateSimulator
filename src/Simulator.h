#pragma once

#include <queue>
#include "Event.h"

class Simulator {
public:
    Simulator();

    uint64_t getCurrentTime() const;
    void scheduleEvent(uint64_t delay, std::shared_ptr<Wire> wire, Signal sig);
    void run();

private:
    uint64_t current_time;
    uint64_t next_event_id;
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> events;
};