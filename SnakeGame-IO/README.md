# 🐍 SNAKE.IO — CONSOLE EDITION
 
<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17-blue.svg?style=for-the-badge&logo=c%2B%2B" alt="C++ Version" />
  <img src="https://img.shields.io/badge/Platform-Windows_Console-0078D6.svg?style=for-the-badge&logo=windows" alt="Platform Support" />
  <img src="https://img.shields.io/badge/Architecture-Modular_OOP-brightgreen.svg?style=for-the-badge" alt="Architecture Pattern" />
</p>

```
██████╗ ███╗   ██╗ █████╗ ██╗  ██╗███████╗      ██╗ ██████╗ 
██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝      ██║██╔═══██╗
╚█████╗ ██╔██╗ ██║███████║█████╔╝ █████╗        ██║██║   ██║
 ╚═══██╗██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝        ██║██║   ██║
██████╔╝██║ ╚████║██║  ██║██║  ██╗███████╗██╗   ██║╚██████╔╝
╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝   ╚═╝ ╚═════╝
```
 
> A Console Based high-performance, modular C++ arcade game built from the ground up — featuring a zero-flicker console-buffer render pipeline, multi-tier runtime asset spawning, and an anti-input-inversion guard.
 
---
 
## 👨‍💻Lead Software Engineer
 
| Role | Detail |
|---|---|
| **Architect** | ***Syed Saad Bin Irfan*** |
| **Institution** | Department of Computer Science, UBIT, University of Karachi |
| **Project Hub** | Part of the Cpp-Engineering-Hub |
 
---
 
## 🎮Game Interface Preview
 
The engine renders a high-fidelity retro grid directly inside the terminal, tracking live game state in real time:
 
```
████████████████████████████████████████████████████████
█                                                      █
█             $                                        █
█                                                      █
█                    o o o Ω                           █
█                                                      █
█                                     ★                
█                                                      █
████████████████████████████████████████████████████████
══════════════════════ ARCADE METRICS ═══════════════════
  CURRENT SCORE  : 40                SESSION HIGH  : 120
  BOUNDARY MODE  : KILLER WALLS      BONUS DECAY : 28
═════════════════════════════════════════════════════════
  [ W A S D ]  Move Snake     |     [ X ]  Emergency Exit
```
 
---
 
## ⚡Core Engineering Upgrades
 
- **Zero-Flicker Buffer Mapping** — Uses Win32 `GetStdHandle` + `SetConsoleCursorPosition` to reset the draw cursor instantly instead of `system("cls")`, hitting ~40ms frames with zero flicker.
- **Multi-Tier Spawning Logic** — Standard food (`$`) grants +10 points; a rare Golden Star (`★`) spawns probabilistically and decays after 35 ticks, rewarding +30 if caught in time.
- **Anti-Self-Inversion Guard** — Blocks the classic instant-reverse exploit by cross-checking current velocity against the tail vector before accepting a new direction.
- **Dual Boundary Modes** — Toggle between strict wall-collision death and wrap-around portal edges.
---
 
## 📁Repository Structure
 
```
SnakeGame-IO/
├── include/
│   ├── Common.hpp        # Global config, enums, ANSI color escapes
│   └── SnakeEngine.hpp   # Core engine class declarations
├── src/
│   ├── SnakeEngine.cpp   # Win32 I/O, movement loop, frame engine
│   └── main.cpp          # Runtime entry point
└── README.md              # This file
```
 
---
 
## 🕹️Control Layout
 
| Action | Key | Matrix Symbol | Console Color |
|---|:---:|:---:|---|
| Move Up | `W` | `Ω` (Head) | Bold Bright Green |
| Move Left | `A` | `o` (Tail Segment) | Standard Green |
| Move Down | `S` | `$` (Standard Fruit) | Bold Bright Red |
| Move Right | `D` | `★` (Golden Asset) | High-Yield Yellow |
| Emergency Exit | `X` | — | — |
 
Press **`X`** at any time to cleanly shut down the game loop and return to the menu.
 
---
 
## 🛠️Build & Compilation
 
**1. Enter the workspace**
```powershell
cd SnakeGame-IO
```
 
**2. Compile with G++ (MinGW)**
```powershell
g++ main.cpp src/SnakeEngine.cpp -I include -Wall -O3 -std=c++17 -o SnakeIO.exe
```
 
**3. Run the Game**
```powershell
./SnakeIO.exe
```
 
---
 
## 💡Key Code Implementations
 
**Direct Win32 Console Cursor Relocation**
```cpp
void SnakeEngine::setCursorPosition(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordinates = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(consoleHandle, coordinates);
}
```
 
**Tail Coordinate Shift Loop**
```cpp
Coordinate previousCoordinate = head;
for (size_t i = 0; i < tail.size(); i++) {
    Coordinate temporarySwapValue = tail[i];
    tail[i] = previousCoordinate;
    previousCoordinate = temporarySwapValue;
}
```
 
---
 
<p align="center"><i>Engineered with high coding standards by Syed Saad Bin Irfan.</i></p> 
