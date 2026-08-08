#pragma once
#include <memory>
#include <cstdint>
#include "Gate.h"
#include "Wire.h"

class Simulator; 

class NotGate : public Gate {
public:
    NotGate(Simulator& sim, std::shared_ptr<Wire> in, std::shared_ptr<Wire> out, uint64_t delay = 5);
    void evaluate() override;

private:
    Simulator& sim;
    std::shared_ptr<Wire> input;
    std::shared_ptr<Wire> output;
    uint64_t delay;
};