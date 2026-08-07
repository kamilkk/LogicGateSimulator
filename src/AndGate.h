#pragma once

#include <memory>
#include "Gate.h"
#include "Wire.h"

class AndGate : public Gate {
public:
    AndGate(std::shared_ptr<Wire> in1, std::shared_ptr<Wire> in2, std::shared_ptr<Wire> out);
    void evaluate() override;

private:
    std::shared_ptr<Wire> input1;
    std::shared_ptr<Wire> input2;
    std::shared_ptr<Wire> output;
};