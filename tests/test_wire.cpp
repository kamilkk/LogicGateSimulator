#include <gtest/gtest.h>
#include "Wire.h"

TEST(WireTest, StateChangeTriggersAction) {
    Wire w;
    bool triggered = false;
    
    w.addAction([&triggered]() { triggered = true; });
    
    // addAction triggers immediately once
    EXPECT_TRUE(triggered); 
    
    triggered = false;
    w.setSignal(Signal::High); // Should trigger again
    EXPECT_EQ(w.getSignal(), Signal::High);
    EXPECT_TRUE(triggered);
}