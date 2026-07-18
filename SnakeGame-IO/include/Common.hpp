#pragma once

// System color tokens
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_MAGENTA "\033[1;35m"
#define COLOR_WHITE   "\033[1;37m"

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum GameMode { KILLER_WALLS = 1, TRANSPARENT_WALLS = 2 };

struct Coordinate {
    int x;
    int y;
};

//This handles all the system tokens, terminal colors, dimensional coordinates, and global configuration enums.