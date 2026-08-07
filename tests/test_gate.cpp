#include <gtest/gtest.h>
#include "Wire.h"
#include "AndGate.h"

TEST(GateTest, AndGateLogic) {
    auto in1 = std::make_shared<Wire>();
    auto in2 = std::make_shared<Wire>();
    auto out = std::make_shared<Wire>();
    
    AndGate and_gate(in1, in2, out);
    
    in1->setSignal(Signal::High);
    in2->setSignal(Signal::Low);
    EXPECT_EQ(out->getSignal(), Signal::Low);
    
    in2->setSignal(Signal::High);
    EXPECT_EQ(out->getSignal(), Signal::High); 
}