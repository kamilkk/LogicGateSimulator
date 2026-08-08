#include <gtest/gtest.h>
#include "Wire.h"
#include "AndGate.h"
#include "XorGate.h"
#include "Simulator.h"

TEST(IntegrationTest, HalfAdder) {
    Simulator sim;
    auto A = std::make_shared<Wire>();
    auto B = std::make_shared<Wire>();
    auto Sum = std::make_shared<Wire>();
    auto Carry = std::make_shared<Wire>();

    XorGate xor1(sim, A, B, Sum, 8); 
    AndGate and1(sim, A, B, Carry, 5);

    A->setSignal(Signal::High);
    B->setSignal(Signal::High);

    sim.run();

    EXPECT_EQ(Sum->getSignal(), Signal::Low);
    EXPECT_EQ(Carry->getSignal(), Signal::High);
}