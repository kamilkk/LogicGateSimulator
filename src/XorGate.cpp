#include "XorGate.h"
#include "Simulator.h"

XorGate::XorGate(Simulator& sim, std::shared_ptr<Wire> in1, std::shared_ptr<Wire> in2, std::shared_ptr<Wire> out, uint64_t delay)
    : sim(sim), input1(in1), input2(in2), output(out), delay(delay) {
    auto evalAction = [this]() { this->evaluate(); };
    input1->addAction(evalAction);
    input2->addAction(evalAction);
}

void XorGate::evaluate() {
    Signal a = input1->getSignal();
    Signal b = input2->getSignal();
    
    if (a == Signal::Unknown || b == Signal::Unknown) {
        sim.scheduleEvent(delay, output, Signal::Unknown);
    } else if (a != b) {
        sim.scheduleEvent(delay, output, Signal::High);
    } else {
        sim.scheduleEvent(delay, output, Signal::Low);
    }
}