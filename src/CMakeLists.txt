add_library(logic_core
    AndGate.cpp
    NotGate.cpp
    OrGate.cpp
    Simulator.cpp
    Wire.cpp
    XorGate.cpp
)
# Expose the src directory to anything that links against logic_core
target_include_directories(logic_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})