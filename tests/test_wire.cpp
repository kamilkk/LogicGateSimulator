#include <gtest/gtest.h>
#include "Wire.h"

TEST(WireTest, StateChangeTriggersAction) {
    Wire w;
    bool triggered = false;
    
    w.addAction([&triggered]() { triggered = true; });
    
    EXPECT_TRUE(triggered); 
    
    triggered = false;
    w.setSignal(Signal::High); 
    EXPECT_EQ(w.getSignal(), Signal::High);
    EXPECT_TRUE(triggered);
}