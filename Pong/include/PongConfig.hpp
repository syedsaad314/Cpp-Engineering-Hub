#ifndef PONG_CONFIG_HPP
#define PONG_CONFIG_HPP

#include <string>

namespace PongEngine {

    // Syed Saad Bin Irfan's System Identity Banners
    const std::string ARCHITECT_NAME = "SYED SAAD BIN IRFAN";

    // ANSI Escape Code System for Terminal Interactivity
    const std::string RESET          = "\033[0m";
    const std::string BOLD           = "\033[1m";
    const std::string FG_RED         = "\033[1;31m";
    const std::string FG_GREEN       = "\033[1;32m";
    const std::string FG_YELLOW      = "\033[1;33m";
    const std::string FG_BLUE        = "\033[1;34m";
    const std::string FG_MAGENTA     = "\033[1;35m";
    const std::string FG_CYAN        = "\033[1;36m";
    const std::string FG_WHITE       = "\033[1;37m";

    enum class GameState {
        MAIN_MENU,
        PLAYING_PVP,
        PLAYING_PVAI,
        SETTINGS,
        QUIT
    };

    enum class Difficulty {
        EASY,
        MEDIUM,
        HARD
    };

    enum eDirection { 
        STOP, 
        RIGHT, 
        UPRIGHT, 
        DOWNRIGHT, 
        LEFT, 
        UPLEFT, 
        DOWNLEFT 
    };
    
    enum eControler { 
        PAUSE, 
        UP, 
        DOWN 
    };

    struct EngineSettings {
        Difficulty aiDifficulty = Difficulty::MEDIUM;
        bool soundEffectsEnabled = true;
        bool useColors = true;
        int maxWinningScore = 5;
        int gameSpeedMs = 35; // Stabilizes rendering cycle rates
    };

} // namespace PongEngine

#endif // PONG_CONFIG_HPP