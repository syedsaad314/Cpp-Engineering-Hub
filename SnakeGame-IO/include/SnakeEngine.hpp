#pragma once
#include <vector>
#include "Common.hpp"

class SnakeEngine {
private:
    // Playfield matrix metrics
    const int width = 50;
    const int height = 20;

    // Game state models
    Coordinate head;
    std::vector<Coordinate> tail;
    Coordinate fruit;
    Coordinate goldenFruit;
    
    Direction dir;
    GameMode mode;
    
    int score;
    int highScore;
    int gameSpeedMs;
    bool isGameOver;
    bool isGoldenFruitActive;
    int goldenFruitTimer;

    // Platform-specific console I/O mechanics
    void hideConsoleCursor();
    void setCursorPosition(int x, int y);
    void spawnFruit();
    void setupGame();
    void displayMainMenu();
    void renderFrame();
    void captureInput();
    void executeLogic();

public:
    SnakeEngine();
    void runEngineLoop();
};

//The class blueprint. It encapsulates all operational parameters, decoupling internal logic checks from the public interface.