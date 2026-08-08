#include <gtest/gtest.h>
#include "Wire.h"
#include "AndGate.h"
#include "Simulator.h"

TEST(GateTest, AndGateLogicWithSimulator) {
    Simulator sim;
    auto in1 = std::make_shared<Wire>();
    auto in2 = std::make_shared<Wire>();
    auto out = std::make_shared<Wire>();
    
    // Inject the simulator into the gate
    AndGate and_gate(sim, in1, in2, out, /*delay=*/ 5);
    
    in1->setSignal(Signal::High);
    in2->setSignal(Signal::Low);
    
    // Output shouldn't change instantly!
    EXPECT_EQ(out->getSignal(), Signal::Unknown);
    
    sim.run(); // Run the event queue
    EXPECT_EQ(out->getSignal(), Signal::Low);
    
    in2->setSignal(Signal::High);
    sim.run();
    EXPECT_EQ(out->getSignal(), Signal::High); 
}