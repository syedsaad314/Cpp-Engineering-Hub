#include "../include/SnakeEngine.hpp"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

SnakeEngine::SnakeEngine() {
    srand(static_cast<unsigned int>(time(0)));
    highScore = 0;
    mode = KILLER_WALLS;
    gameSpeedMs = 100;
    isGameOver = false;
}

void SnakeEngine::hideConsoleCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void SnakeEngine::setCursorPosition(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordinates = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(consoleHandle, coordinates);
}

void SnakeEngine::spawnFruit() {
    while (true) {
        fruit.x = rand() % width;
        fruit.y = rand() % height;
        if (fruit.x == head.x && fruit.y == head.y) continue;
        
        bool onTail = false;
        for (const auto& segment : tail) {
            if (segment.x == fruit.x && segment.y == fruit.y) {
                onTail = true;
                break;
            }
        }
        if (!onTail) break;
    }

    if (rand() % 5 == 0 && !isGoldenFruitActive) {
        while (true) {
            goldenFruit.x = rand() % width;
            goldenFruit.y = rand() % height;
            if ((goldenFruit.x == head.x && goldenFruit.y == head.y) || 
                (goldenFruit.x == fruit.x && goldenFruit.y == fruit.y)) continue;

            bool onTail = false;
            for (const auto& segment : tail) {
                if (segment.x == goldenFruit.x && segment.y == goldenFruit.y) {
                    onTail = true;
                    break;
                }
            }
            if (!onTail) {
                isGoldenFruitActive = true;
                goldenFruitTimer = 35; 
                break;
            }
        }
    }
}

void SnakeEngine::displayMainMenu() {
    system("cls");
    hideConsoleCursor();
    
    // High-Fidelity Corrected SNAKE.IO Banner
    std::cout << COLOR_GREEN;
    std::cout << "  ██████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗      ██╗ ██████╗ \n";
    std::cout << " ██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝      ██║██╔═══██╗\n";
    std::cout << " ╚█████╗ ██╔██╗ ██║███████║█████╔╝ █████╗        ██║██║   ██║\n";
    std::cout << "  ╚═══██╗██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝        ██║██║   ██║\n";
    std::cout << " ██████╔╝██║ ╚████║██║  ██║██║  ██╗███████╗██╗   ██║╚██████╔╝\n";
    std::cout << " ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝   ╚═╝ ╚═════╝ \n" << COLOR_RESET;
    std::cout << COLOR_CYAN << " ═══════════════════════════════════════════════════════════════\n" << COLOR_RESET;
    std::cout << "    [SYSTEM STATUS: READY] | [SNAKE.IO PRODUCTION RUNTIME]\n\n";
    
    std::cout << COLOR_WHITE << " [1] ENVIRONMENT SELECTOR:\n" << COLOR_RESET;
    std::cout << "     1. Killer Classic Walls (Strict Boundary Box)\n";
    std::cout << "     2. Transparent Portal Walls (Wrap-Around Loop)\n\n";
    std::cout << " --> Choose Matrix Mode (1-2): ";
    
    int choice;
    std::cin >> choice;
    mode = (choice == 2) ? TRANSPARENT_WALLS : KILLER_WALLS;

    std::cout << COLOR_WHITE << "\n [2] VELOCITY CONFIGURATION:\n" << COLOR_RESET;
    std::cout << "     1. Casual Processing Mode (Relaxed Gameplay)\n";
    std::cout << "     2. Intermediate Loop Mode (Balanced Challenge)\n";
    std::cout << "     3. Expert Execution Mode  (Hyper Velocity Real-time)\n\n";
    std::cout << " --> Select Velocity Level (1-3): ";
    
    std::cin >> choice;
    if (choice == 1) gameSpeedMs = 150;
    else if (choice == 3) gameSpeedMs = 40;
    else gameSpeedMs = 80;

    std::cin.clear();
    fflush(stdin);
}

void SnakeEngine::setupGame() {
    isGameOver = false;
    dir = STOP;
    head.x = width / 2;
    head.y = height / 2;
    score = 0;
    isGoldenFruitActive = false;
    goldenFruitTimer = 0;
    tail.clear();
    
    system("cls");
    spawnFruit();
}

void SnakeEngine::renderFrame() {
    setCursorPosition(0, 0);

    std::cout << COLOR_CYAN;
    for (int i = 0; i < width + 2; i++) std::cout << "█";
    std::cout << "\n" << COLOR_RESET;

    for (int i = 0; i < height; i++) {
        std::cout << COLOR_CYAN << "█" << COLOR_RESET; 

        for (int j = 0; j < width; j++) {
            if (i == head.y && j == head.x) {
                std::cout << COLOR_GREEN << "Ω" << COLOR_RESET; 
            } 
            else if (i == fruit.y && j == fruit.x) {
                std::cout << COLOR_RED << "$" << COLOR_RESET; 
            } 
            else if (isGoldenFruitActive && i == goldenFruit.y && j == goldenFruit.x) {
                std::cout << COLOR_YELLOW << "★" << COLOR_RESET; 
            } 
            else {
                bool isTailPrinted = false;
                for (const auto& segment : tail) {
                    if (segment.x == j && segment.y == i) {
                        std::cout << COLOR_GREEN << "o" << COLOR_RESET; 
                        isTailPrinted = true;
                        break;
                    }
                }
                if (!isTailPrinted) std::cout << " ";
            }
        }
        std::cout << COLOR_CYAN << "█\n" << COLOR_RESET; 
    }

    std::cout << COLOR_CYAN;
    for (int i = 0; i < width + 2; i++) std::cout << "█";
    std::cout << "\n" << COLOR_RESET;

    std::cout << COLOR_WHITE << " ═════════════════════ ENGINE METRICS ═════════════════════\n" << COLOR_RESET;
    std::cout << "  CURRENT SCORE : " << COLOR_GREEN << score << COLOR_RESET << "   |   ";
    std::cout << "SESSION HIGH RECORD : " << COLOR_YELLOW << highScore << COLOR_RESET << "\n";
    std::cout << "  SYSTEM MATRIX : " << (mode == KILLER_WALLS ? COLOR_RED "KILLER WALLS" : COLOR_MAGENTA "TRANSPARENT BOUNDS") << COLOR_RESET;
    
    if (isGoldenFruitActive) {
        std::cout << "  |  " << COLOR_YELLOW << "BONUS DECAY COUNTER: [" << goldenFruitTimer << "] " << COLOR_RESET;
    } else {
        std::cout << "  |  " << COLOR_WHITE << "BONUS MATRIX STATE: STABLE      " << COLOR_RESET;
    }
    std::cout << "\n ══════════════════════════════════════════════════════════\n";
    std::cout << "  [W,A,S,D] Guide Vector Velocity Control | Press [X] Emergency Exit\n";
}

void SnakeEngine::captureInput() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': case 'A': if (dir != RIGHT || tail.empty()) dir = LEFT; break;
            case 'd': case 'D': if (dir != LEFT || tail.empty()) dir = RIGHT; break;
            case 'w': case 'W': if (dir != DOWN || tail.empty()) dir = UP; break;
            case 's': case 'S': if (dir != UP || tail.empty()) dir = DOWN; break;
            case 'x': case 'X': isGameOver = true; break;
        }
    }
}

void SnakeEngine::executeLogic() {
    if (dir == STOP) return;

    if (isGoldenFruitActive) {
        goldenFruitTimer--;
        if (goldenFruitTimer <= 0) isGoldenFruitActive = false;
    }

    Coordinate previousCoordinate = head;
    for (size_t i = 0; i < tail.size(); i++) {
        Coordinate temporarySwapValue = tail[i];
        tail[i] = previousCoordinate;
        previousCoordinate = temporarySwapValue;
    }

    switch (dir) {
        case LEFT:  head.x--; break;
        case RIGHT: head.x++; break;
        case UP:    head.y--; break;
        case DOWN:  head.y++; break;
        default: break;
    }

    if (mode == KILLER_WALLS) {
        if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height) {
            isGameOver = true;
            return;
        }
    } else if (mode == TRANSPARENT_WALLS) {
        if (head.x < 0) head.x = width - 1;
        else if (head.x >= width) head.x = 0;
        if (head.y < 0) head.y = height - 1;
        else if (head.y >= height) head.y = 0;
    }

    for (const auto& segment : tail) {
        if (segment.x == head.x && segment.y == head.y) {
            isGameOver = true;
            return;
        }
    }

    if (head.x == fruit.x && head.y == fruit.y) {
        score += 10;
        if (score > highScore) highScore = score;
        tail.push_back({0, 0});
        spawnFruit();
    }

    if (isGoldenFruitActive && head.x == goldenFruit.x && head.y == goldenFruit.y) {
        score += 30;
        if (score > highScore) highScore = score;
        isGoldenFruitActive = false;
        tail.push_back({0, 0});
    }
}

void SnakeEngine::runEngineLoop() {
    while (true) {
        displayMainMenu();
        setupGame();

        while (!isGameOver) {
            renderFrame();
            captureInput();
            executeLogic();
            Sleep(gameSpeedMs);
        }

        system("cls");
        std::cout << "\n\n" << COLOR_RED;
        std::cout << "  ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ \n";
        std::cout << " ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗\n";
        std::cout << " ██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝\n";
        std::cout << " ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗\n";
        std::cout << " ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║\n";
        std::cout << "  ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝\n" << COLOR_RESET;
        
        std::cout << COLOR_WHITE << "\n ══════════════════════ FINAL LEDGER ══════════════════════\n" << COLOR_RESET;
        std::cout << "  CLOSING SCORE ACHIEVED  : " << COLOR_GREEN << score << COLOR_RESET << "\n";
        std::cout << "  SESSION HISTORIC RECORD : " << COLOR_YELLOW << highScore << COLOR_RESET << "\n";
        std::cout << " ══════════════════════════════════════════════════════════\n\n";
        std::cout << "  --> Do you want to re-engage matrix interface? (Y/N): ";
        
        char retryChoice;
        std::cin >> retryChoice;
        if (retryChoice != 'y' && retryChoice != 'Y') {
            std::cout << COLOR_CYAN << "\n [!] Core Console Engine Terminated. System clear.\n" << COLOR_RESET;
            break;
        }
    }
}