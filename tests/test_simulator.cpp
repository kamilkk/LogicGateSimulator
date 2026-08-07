#include <gtest/gtest.h>
#include "Wire.h"
#include "AndGate.h"
#include "Simulator.h"

TEST(SimulatorTest, SimulatorAdvancesTime) {
    Simulator sim;
    auto in1 = std::make_shared<Wire>();
    auto in2 = std::make_shared<Wire>();
    auto out = std::make_shared<Wire>();
    
    AndGate and_gate(sim, in1, in2, out, 10); 
    
    in1->setSignal(Signal::High);
    in2->setSignal(Signal::High);
    
    EXPECT_EQ(out->getSignal(), Signal::Unknown); 
    
    sim.run();
    
    EXPECT_EQ(sim.getCurrentTime(), 10);
    EXPECT_EQ(out->getSignal(), Signal::High);
}