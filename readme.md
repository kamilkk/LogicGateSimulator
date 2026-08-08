## Event-Driven Logic Gate Simulator

A modern C++ (C++17) hardware logic simulator built with an event-driven architecture. This project demonstrates best practices in software engineering, including Dependency Injection, separation of concerns, and robust unit testing.

It features a core simulation engine (compiled as a static library) and a Terminal User Interface (TUI) to visualize cascading propagation delays across multi-input combinatorial logic circuits.

### Project Structure
- `src/`: The core event-driven simulation engine and fundamental gate implementations (AND, OR, XOR, NOT).
- `tests/`: A comprehensive GoogleTest suite verifying wire logic, gate behavior, the event queue, and full integration (e.g., Half Adder).
- `src/main.cpp`: An interactive test bench built with [FTXUI](https://github.com/ArthurSonzogni/FTXUI).

### Dependencies
- A C++17 compatible compiler
- CMake (3.14+)
- GoogleTest and FTXUI (both automatically fetched via CMake)

### How to Build

1. Clone the repository and enter the directory:
   ```bash
   git clone https://github.com/kamilkk/LogicGateSimulator
   cd LogicGateSimulator
   ```

2. Generate the build system:
   ```bash
   cmake -S . -B build
   ```

3. Build the project:
   ```bash
   cmake --build build
   ```

### How to Run the TUI

After building, start the interactive logic gate test bench:

```bash
./build/MySimulator
```
### How to Run Tests

The project uses CTest to manage the GoogleTest suite. To run all verification tests:

```bash
ctest --test-dir build --output-on-failure
```