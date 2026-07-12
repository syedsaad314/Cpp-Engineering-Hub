#ifndef HANGMAN_CONFIG_HPP
#define HANGMAN_CONFIG_HPP

#include <string>
#include <vector>

namespace HangmanEngine {

    // ANSI Escape Code System for Terminal Interactivity
    const std::string RESET          = "\033[0m";
    const std::string BOLD           = "\033[1m";
    const std::string UNDERLINE      = "\033[4m";
    const std::string FG_RED         = "\033[1;31m";
    const std::string FG_GREEN       = "\033[1;32m";
    const std::string FG_YELLOW      = "\033[1;33m";
    const std::string FG_BLUE        = "\033[1;34m";
    const std::string FG_MAGENTA     = "\033[1;35m";
    const std::string FG_CYAN        = "\033[1;36m";
    const std::string FG_WHITE       = "\033[1;37m";
    const std::string BG_DARK_GRAY   = "\033[48;5;234m";
    const std::string BG_NAVY        = "\033[48;5;18m";

    enum class GameState {
        MAIN_MENU,
        PLAYING,
        SETTINGS,
        STATS_BOARD,
        QUIT
    };

    enum class Difficulty {
        EASY,
        MEDIUM,
        HARD
    };

    struct PlayerProfile {
        int totalWins = 0;
        int totalLosses = 0;
        int currentStreak = 0;
        int bestStreak = 0;
        int totalHintsUsed = 0;
    };

    struct GameSettings {
        Difficulty currentDifficulty = Difficulty::MEDIUM;
        bool useColors = true;
        int maximumAllowedMisses = 10; // Matches user baseline count criteria
    };

} // namespace HangmanEngine

#endif // HANGMAN_CONFIG_HPP