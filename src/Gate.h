#pragma once

class Gate {
public:
    virtual ~Gate() = default;
    virtual void evaluate() = 0; 
};