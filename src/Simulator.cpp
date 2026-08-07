#include "Simulator.h"

Simulator::Simulator() : current_time(0), next_event_id(0) {}

uint64_t Simulator::getCurrentTime() const { 
    return current_time; 
}

void Simulator::scheduleEvent(uint64_t delay, std::shared_ptr<Wire> wire, Signal sig) {
    events.push({current_time + delay, wire, sig, next_event_id++});
}

void Simulator::run() {
    while (!events.empty()) {
        Event e = events.top();
        events.pop();
        
        current_time = e.time; 
        e.target_wire->setSignal(e.new_signal);
    }
}