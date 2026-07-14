# 🏓 TERMINAL PONG v2.0

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17-blue.svg?style=for-the-badge&logo=c%2B%2B" alt="C++ Version" />
  <img src="https://img.shields.io/badge/Platform-Windows_Console-0078D6.svg?style=for-the-badge&logo=windows" alt="Platform Support" />
  <img src="https://img.shields.io/badge/Architecture-Modular_OOP-brightgreen.svg?style=for-the-badge" alt="Architecture Pattern" />
</p>

```text
 ██████╗  ██████╗ ███╗   ██╗ ██████╗ 
 ██╔══██╗██╔═══██╗████╗  ██║██╔════╝ 
 ██████╔╝██║   ██║██╔██╗ ██║██║  ███╗
 ██╔═══╝ ██║   ██║██║╚██╗██║██║   ██║
 ██║     ╚██████╔╝██║ ╚████║╚██████╔╝
 ╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚══════╝ 
```

> **A high-performance, modular C++ interactive arcade engine built from the ground up.** Refactored from a legacy procedural file into an optimized, Object-Oriented software architecture featuring a zero-flicker double-buffer render pipeline, adaptive AI systems, and low-latency hardware sound wave generation.

---

## 👨‍💻 Lead Software Engineer
*   **Architect:** **Syed Saad Bin Irfan**
*   **Institution:** Department of Computer Science, UBIT, University of Karachi
*   **Project Hub:** Part of the [Cpp-Engineering-Hub](https://github.com/syedsaad314/Cpp-Engineering-Hub)

---

## 🎮 Game Interface Preview

The game compiles and renders a retro CRT-style playground directly inside your command line interface:

```text
  ╔══════════════════════════════════════════════════════╗
  ║   P1: 4                                    P2/AI: 2  ║
  ╠══════════════════════════════════════════════════════╣
  ║ █                                                    ║
  ║ █                       o                            ║
  ║ █                                                    ║
  ║                                                    █ ║
  ║                                                    █ ║
  ║                                                    █ ║
  ╚══════════════════════════════════════════════════════╝
```

---

## ⚡ Core Engineering Upgrades

This project demonstrates advanced console manipulation and low-level system design by resolving several standard command-line bottlenecks:

*   **Zero-Flicker Double-Buffered Rendering:** Classic terminal games flicker heavily because they clear and redraw the console character-by-character. This engine builds the entire frame in memory inside a `std::stringstream` and flushes it to the screen buffer in one atomic operation while hiding the hardware cursor.
*   **Adaptive CPU AI Opponent:** Play solo against an AI opponent that uses configurable tracking probabilities (Easy, Medium, Hard) to simulate real human reactions.
*   **Dynamic Sound Synthesis:** Uses the Windows Hardware API (`Beep`) to generate frequency-modulated retro sound effects in real-time when the ball hits a paddle, bounces off walls, or scores a goal.
*   **ANSI Color Integration:** Complete support for clean, readable console colors highlighting paddles, targets, scores, and menu nodes.
*   **Strict Memory Safety (RAII):** Patched a major memory leak in the legacy model by implementing absolute resource management inside class destructors.

---

## 📁 Repository Directory Structure

```text
Pong/
├── include/
│   ├── PongConfig.hpp  # Global constants, ANSI colors, and Syed Saad Bin Irfan's credentials
│   ├── Ball.hpp        # Object interface for physics vector translations
│   ├── Paddle.hpp      # Object interface for console boundaries and position rules
│   └── GameEngine.hpp  # Central coordinator managing game loop states & double buffers
├── src/
│   ├── Ball.cpp        # Real-time vector calculation and collision routing
│   ├── Paddle.cpp      # Paddle movement and step bounds
│   └── GameEngine.cpp  # System initialization, AI rendering, and UI states
├── main.cpp            # Project runtime entry point
└── README.md           # Professional project documentation
```

---

## 🕹️ Control Layout

| Controller Node | Move Up | Move Down | Paddle Color |
| :---: | :---: | :---: | :---: |
| **Player 1** | <kbd>W</kbd> | <kbd>S</kbd> | Green |
| **Player 2 / AI** | <kbd>I</kbd> | <kbd>J</kbd> | Blue |

*   **System Exit:** Press <kbd>Q</kbd> to safely shut down game threads and return to the main menu.

---

## 🛠️ Build & Compilation Pipeline

Compile and run this project without any external graphics frameworks.

### 1. Step into the Workspace
```powershell
cd Pong
```

### 2. Run the G++ Compiler
```powershell
g++ main.cpp src/Ball.cpp src/Paddle.cpp src/GameEngine.cpp -I include -Wall -O3 -std=c++17 -o TerminalPong.exe
```

### 3. Launch the Executable
```powershell
./TerminalPong.exe
```

---

## 💡 Key Code Implementations

### Zero-Flicker Console Buffer Mapping
```cpp
// Set hardware console cursor back to (0,0) instead of running heavy "cls" calls
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
```

### Automatic Resource Cleanup (RAII)
```cpp
GameEngine::~GameEngine() {
    delete gameBall;
    delete paddlePlayer1;
    delete paddlePlayer2;
}
```

---
<p align="center"><i>Engineered with high coding standards by Syed Saad Bin Irfan.</i></p>