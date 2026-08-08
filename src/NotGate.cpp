#include "NotGate.h"
#include "Simulator.h"

NotGate::NotGate(Simulator& sim, std::shared_ptr<Wire> in, std::shared_ptr<Wire> out, uint64_t delay)
    : sim(sim), input(in), output(out), delay(delay) {
    auto evalAction = [this]() { this->evaluate(); };
    input->addAction(evalAction);
}

void NotGate::evaluate() {
    Signal a = input->getSignal();
    if (a == Signal::Unknown) {
        sim.scheduleEvent(delay, output, Signal::Unknown);
    } else if (a == Signal::High) {
        sim.scheduleEvent(delay, output, Signal::Low);
    } else {
        sim.scheduleEvent(delay, output, Signal::High);
    }
}