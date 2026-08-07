#pragma once

#include <memory>
#include <cstdint>
#include "Gate.h"
#include "Wire.h"

// Forward declaration to avoid circular dependencies
class Simulator; 

class AndGate : public Gate {
public:
    AndGate(Simulator& sim, std::shared_ptr<Wire> in1, std::shared_ptr<Wire> in2, std::shared_ptr<Wire> out, uint64_t delay = 5);
    void evaluate() override;

private:
    Simulator& sim;
    std::shared_ptr<Wire> input1;
    std::shared_ptr<Wire> input2;
    std::shared_ptr<Wire> output;
    uint64_t delay;
};