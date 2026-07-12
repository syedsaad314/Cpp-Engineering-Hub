#include "../include/DisplayManager.hpp"
#include <iostream>
#include <algorithm>

namespace HangmanEngine {

    DisplayManager::DisplayManager(GameSettings& engineSettings) : settings(engineSettings) {}

    void DisplayManager::ClearConsole() const {
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif
    }

    void DisplayManager::PrintBoxMessage(std::string message, bool printTop, bool printBottom, std::string colorTheme) const {
        std::string theme = settings.useColors ? colorTheme : "";
        std::string reset = settings.useColors ? RESET : "";

        if (printTop) {
            std::cout << theme << "+";
            for (int i = 0; i < boxWidth - 2; ++i) std::cout << "-";
            std::cout << "+" << reset << std::endl;
        }

        std::cout << theme << "|" << reset;

        // Custom balancing engine extracted from user algorithm
        bool toggleSide = true;
        int printableSpace = boxWidth - 2;
        
        while (static_cast<int>(message.length()) < printableSpace) {
            if (toggleSide) {
                message = message + " ";
            } else {
                message = " " + message;
            }
            toggleSide = !toggleSide;
        }

        std::cout << FG_WHITE << message << theme << "|" << reset << std::endl;

        if (printBottom) {
            std::cout << theme << "+";
            for (int i = 0; i < boxWidth - 2; ++i) std::cout << "-";
            std::cout << "+" << reset << std::endl;
        }
    }

    void DisplayManager::DrawVisualScaffold(int guessCount) const {
        std::string clr = settings.useColors ? FG_RED : "";
        std::string ropeClr = settings.useColors ? FG_YELLOW : "";
        
        // Base structure elements scaled seamlessly up to 10 distinct error segments
        PrintBoxMessage(guessCount >= 1 ? "  +---+" : "  +", false, false, clr);
        PrintBoxMessage(guessCount >= 2 ? "  |   |" : "  |", false, false, ropeClr);
        
        if (guessCount == 10) {
            PrintBoxMessage(" [X]  |", false, false, clr);
        } else if (guessCount >= 3) {
            PrintBoxMessage("  O   |", false, false, clr);
        } else {
            PrintBoxMessage("      |", false, false, clr);
        }

        if (guessCount == 4)  PrintBoxMessage("  |   |", false, false, clr);
        else if (guessCount == 5)  PrintBoxMessage(" \\|   |", false, false, clr);
        else if (guessCount >= 6)  PrintBoxMessage(" \\|/  |", false, false, clr);
        else PrintBoxMessage("      |", false, false, clr);

        if (guessCount >= 7)  PrintBoxMessage("  |   |", false, false, clr);
        else PrintBoxMessage("      |", false, false, clr);

        if (guessCount == 8)  PrintBoxMessage(" /    |", false, false, clr);
        else if (guessCount >= 9)  PrintBoxMessage(" / \\  |", false, false, clr);
        else PrintBoxMessage("      |", false, false, clr);

        PrintBoxMessage("=========", false, false, clr);
    }

    void DisplayManager::DisplayRemainingAlphabet(const std::string& guessedLetters) const {
        PrintBoxMessage("REMAINING AVAILABILITY MATRIX", true, true, FG_CYAN);
        
        auto buildRow = [&](char start, char end) {
            std::string lineStr = "";
            for (char c = start; c <= end; ++c) {
                if (guessedLetters.find(c) == std::string::npos) {
                    lineStr += c;
                    lineStr += " ";
                } else {
                    lineStr += ". "; // Mark as selected cleanly
                }
            }
            PrintBoxMessage(lineStr, false, false, FG_CYAN);
        };

        buildRow('a', 'm');
        buildRow('n', 'z');
        PrintBoxMessage("", false, true, FG_CYAN);
    }

    void DisplayManager::DisplayWordProgress(const std::string& wordToGuess, const std::string& guessedLetters) const {
        PrintBoxMessage("CURRENT TARGET SCHEMA", true, true, FG_GREEN);
        std::string evaluationBuffer = "";
        
        for (char character : wordToGuess) {
            if (character == ' ') {
                evaluationBuffer += "  ";
            } else if (guessedLetters.find(character) != std::string::npos) {
                evaluationBuffer += character;
                evaluationBuffer += " ";
            } else {
                evaluationBuffer += "_ ";
            }
        }
        
        PrintBoxMessage(evaluationBuffer, false, true, FG_GREEN);
    }

    void DisplayManager::DisplayHeaderBanner(const std::string& title) const {
        std::string decor = settings.useColors ? (FG_BLUE + BOLD) : "";
        PrintBoxMessage(title, true, true, decor);
    }

    void DisplayManager::DisplayMainMenu() const {
        ClearConsole();
        DisplayHeaderBanner("HANGMAN CORE COMPILATION ENGINE");
        PrintBoxMessage("1. INITIALIZE NEW SOFTWARE SESSION", false, false, FG_WHITE);
        PrintBoxMessage("2. VIEW PLAYER ENGINE STATISTICS", false, false, FG_WHITE);
        PrintBoxMessage("3. CONFIGURATION UTILITIES", false, false, FG_WHITE);
        PrintBoxMessage("4. DISCONNECT REPOSITORY CONNECTION", false, true, FG_WHITE);
        std::cout << "\n" << FG_CYAN << "EXECUTE COMMAND INTENT > " << RESET;
    }

    void DisplayManager::DisplayPlayerStats(const PlayerProfile& profile) const {
        ClearConsole();
        DisplayHeaderBanner("ANALYTIC HISTOGRAM MONITOR");
        PrintBoxMessage("TOTAL SESSIONS WON  : " + std::to_string(profile.totalWins), false, false, FG_GREEN);
        PrintBoxMessage("TOTAL SESSIONS LOST : " + std::to_string(profile.totalLosses), false, false, FG_RED);
        PrintBoxMessage("CURRENT LIVE STREAK : " + std::to_string(profile.currentStreak), false, false, FG_YELLOW);
        PrintBoxMessage("HISTORIC PEAK STREAK: " + std::to_string(profile.bestStreak), false, false, FG_MAGENTA);
        PrintBoxMessage("HINT SYSTEMS UTALIZED: " + std::to_string(profile.totalHintsUsed), false, true, FG_CYAN);
        std::cout << "\n" << FG_YELLOW << "PRESS ANY KEY TO RETURN TO ROOT CONSOLE..." << RESET;
    }

    void DisplayManager::DisplaySettingsMenu() const {
        ClearConsole();
        DisplayHeaderBanner("SYSTEM METRIC PARAMETERS");
        std::string diffStr = (settings.currentDifficulty == Difficulty::EASY) ? "EASY" : 
                              (settings.currentDifficulty == Difficulty::MEDIUM) ? "MEDIUM" : "HARD";
        
        PrintBoxMessage("1. MODIFY COMPLEXITY LAYER [" + diffStr + "]", false, false, FG_WHITE);
        PrintBoxMessage("2. TOGGLE ANSI COLOR MATRIX [" + std::string(settings.useColors ? "ENABLED" : "DISABLED") + "]", false, false, FG_WHITE);
        PrintBoxMessage("3. SET CRITICAL ERROR LIMIT [" + std::to_string(settings.maximumAllowedMisses) + " TRIES]", false, false, FG_WHITE);
        PrintBoxMessage("4. RETURN TO ROOT DIRECTORY CONSOLE", false, true, FG_WHITE);
        std::cout << "\n" << FG_CYAN << "SELECT CONFIGURATION NODE > " << RESET;
    }

} // namespace HangmanEngine