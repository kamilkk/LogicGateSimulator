#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <memory>
#include <vector>
#include "Wire.h"
#include "AndGate.h"
#include "OrGate.h"
#include "XorGate.h"
#include "NotGate.h"
#include "Simulator.h"

using namespace ftxui;

std::string sigToStr(Signal s) {
    if (s == Signal::High) return "1 (High)";
    if (s == Signal::Low) return "0 (Low)";
    return "? (Unknown)";
}

int main() {
    Simulator sim;
    
    // 4 Inputs
    auto A = std::make_shared<Wire>();
    auto B = std::make_shared<Wire>();
    auto C = std::make_shared<Wire>();
    auto D = std::make_shared<Wire>();
    
    // Wires for 2-Input Gates (and NOT)
    auto OutAnd2 = std::make_shared<Wire>();
    auto OutOr2  = std::make_shared<Wire>();
    auto OutXor2 = std::make_shared<Wire>();
    auto OutNot  = std::make_shared<Wire>();

    // Wires for 3-Input Gates
    auto And3_Temp = std::make_shared<Wire>();
    auto Out_And3 = std::make_shared<Wire>();
    
    auto Or3_Temp = std::make_shared<Wire>();
    auto Out_Or3 = std::make_shared<Wire>();

    // Wires for 4-Input Gates
    auto And4_T1 = std::make_shared<Wire>();
    auto And4_T2 = std::make_shared<Wire>();
    auto Out_And4 = std::make_shared<Wire>();

    auto Or4_T1 = std::make_shared<Wire>();
    auto Or4_T2 = std::make_shared<Wire>();
    auto Out_Or4 = std::make_shared<Wire>();
    
    // --- 2-Input Gates (and NOT) ---
    AndGate and2(sim, A, B, OutAnd2, 5);
    OrGate  or2(sim, A, B, OutOr2, 5);
    XorGate xor2(sim, A, B, OutXor2, 8); 
    NotGate not1(sim, A, OutNot, 2); 

    // --- Compose 3-Input AND (Delay: 5 + 5 = 10) ---
    AndGate and3_stage1(sim, A, B, And3_Temp, 5);
    AndGate and3_stage2(sim, And3_Temp, C, Out_And3, 5);

    // --- Compose 3-Input OR (Delay: 5 + 5 = 10) ---
    OrGate or3_stage1(sim, A, B, Or3_Temp, 5);
    OrGate or3_stage2(sim, Or3_Temp, C, Out_Or3, 5);

    // --- Compose 4-Input AND (Delay: 5 + 5 = 10 because T1/T2 are parallel) ---
    AndGate and4_stage1_A(sim, A, B, And4_T1, 5);
    AndGate and4_stage1_B(sim, C, D, And4_T2, 5);
    AndGate and4_stage2(sim, And4_T1, And4_T2, Out_And4, 5);

    // --- Compose 4-Input OR (Delay: 5 + 5 = 10 because T1/T2 are parallel) ---
    OrGate or4_stage1_A(sim, A, B, Or4_T1, 5);
    OrGate or4_stage1_B(sim, C, D, Or4_T2, 5);
    OrGate or4_stage2(sim, Or4_T1, Or4_T2, Out_Or4, 5);

    // Initialize all to Low
    A->setSignal(Signal::Low);
    B->setSignal(Signal::Low);
    C->setSignal(Signal::Low);
    D->setSignal(Signal::Low);

    bool togA = false, togB = false, togC = false, togD = false;
    auto cbA = Checkbox("Input A", &togA);
    auto cbB = Checkbox("Input B", &togB);
    auto cbC = Checkbox("Input C", &togC);
    auto cbD = Checkbox("Input D", &togD);
    auto input_container = Container::Vertical({cbA, cbB, cbC, cbD});

    auto renderer = Renderer(input_container, [&] {
        Signal nA = togA ? Signal::High : Signal::Low;
        Signal nB = togB ? Signal::High : Signal::Low;
        Signal nC = togC ? Signal::High : Signal::Low;
        Signal nD = togD ? Signal::High : Signal::Low;
        
        if (A->getSignal() != nA) sim.scheduleEvent(0, A, nA);
        if (B->getSignal() != nB) sim.scheduleEvent(0, B, nB);
        if (C->getSignal() != nC) sim.scheduleEvent(0, C, nC);
        if (D->getSignal() != nD) sim.scheduleEvent(0, D, nD);
        
        sim.run();

        return vbox({
            text("🛠️  Advanced Cascaded Test Bench") | bold,
            separator(),
            hbox({
                window(text("Inputs"), input_container->Render()),
                window(text("Outputs"), vbox({
                    text("2-Input AND (A,B):     " + sigToStr(OutAnd2->getSignal())),
                    text("2-Input OR  (A,B):     " + sigToStr(OutOr2->getSignal())),
                    text("2-Input XOR (A,B):     " + sigToStr(OutXor2->getSignal())),
                    text("NOT A:                 " + sigToStr(OutNot->getSignal())),
                    separator(),
                    text("3-Input AND (A,B,C):   " + sigToStr(Out_And3->getSignal())),
                    text("3-Input OR  (A,B,C):   " + sigToStr(Out_Or3->getSignal())),
                    separator(),
                    text("4-Input AND (A,B,C,D): " + sigToStr(Out_And4->getSignal())),
                    text("4-Input OR  (A,B,C,D): " + sigToStr(Out_Or4->getSignal())),
                    separator(),
                    text("Sim Time: " + std::to_string(sim.getCurrentTime()))
                })) | flex
            })
        }) | border;
    });

    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);

    return 0;
}