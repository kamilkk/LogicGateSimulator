#include "AndGate.h"

AndGate::AndGate(std::shared_ptr<Wire> in1, std::shared_ptr<Wire> in2, std::shared_ptr<Wire> out)
    : input1(in1), input2(in2), output(out) {
    
    auto evalAction = [this]() { this->evaluate(); };
    input1->addAction(evalAction);
    input2->addAction(evalAction);
}

void AndGate::evaluate() {
    Signal a = input1->getSignal();
    Signal b = input2->getSignal();
    
    if (a == Signal::High && b == Signal::High) {
        output->setSignal(Signal::High);
    } else if (a == Signal::Unknown || b == Signal::Unknown) {
        output->setSignal(Signal::Unknown);
    } else {
        output->setSignal(Signal::Low);
    }
}