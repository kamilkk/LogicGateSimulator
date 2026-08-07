#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <memory>
#include "Wire.h"
#include "AndGate.h"
#include "Simulator.h"

using namespace ftxui;

std::string sigToStr(Signal s) {
    if (s == Signal::High) return "1 (High)";
    if (s == Signal::Low) return "0 (Low)";
    return "? (Unknown)";
}

int main() {
    Simulator sim;
    auto A = std::make_shared<Wire>();
    auto B = std::make_shared<Wire>();
    auto Sum = std::make_shared<Wire>();
    auto Carry = std::make_shared<Wire>();
    
    AndGate and1(sim, A, B, Carry, 5);

    A->setSignal(Signal::Low);
    B->setSignal(Signal::Low);

    bool toggle_A = false;
    bool toggle_B = false;

    auto cb_a = Checkbox("Input A", &toggle_A);
    auto cb_b = Checkbox("Input B", &toggle_B);
    auto input_container = Container::Vertical({cb_a, cb_b});

    // Capture `sim` by reference in the lambda
    auto renderer = Renderer(input_container, [&] {
        Signal newA = toggle_A ? Signal::High : Signal::Low;
        Signal newB = toggle_B ? Signal::High : Signal::Low;
        
        if (A->getSignal() != newA) sim.scheduleEvent(0, A, newA);
        if (B->getSignal() != newB) sim.scheduleEvent(0, B, newB);
        
        sim.run();

        return vbox({
            text("🛠️  Logic Gate Simulator (Half Adder)") | bold,
            separator(),
            hbox({
                window(text("Inputs"), input_container->Render()),
                window(text("Outputs"), vbox({
                    text("Sum:   " + sigToStr(Sum->getSignal())),
                    text("Carry: " + sigToStr(Carry->getSignal())),
                    text("Sim Time: " + std::to_string(sim.getCurrentTime()))
                })) | flex
            })
        }) | border;
    });

    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);

    return 0;
}