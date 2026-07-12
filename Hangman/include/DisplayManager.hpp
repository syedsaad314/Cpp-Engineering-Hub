#ifndef DISPLAY_MANAGER_HPP
#define DISPLAY_MANAGER_HPP

#include "HangmanConfig.hpp"
#include <string>
#include <vector>

namespace HangmanEngine {

    class DisplayManager {
    private:
        GameSettings& settings;
        const int boxWidth = 50; // Expanded visual container box width

    public:
        explicit DisplayManager(GameSettings& engineSettings);

        void ClearConsole() const;
        void PrintBoxMessage(std::string message, bool printTop = true, bool printBottom = true, std::string colorTheme = "") const;
        void DrawVisualScaffold(int guessCount) const;
        void DisplayRemainingAlphabet(const std::string& guessedLetters) const;
        void DisplayWordProgress(const std::string& wordToGuess, const std::string& guessedLetters) const;
        void DisplayHeaderBanner(const std::string& title) const;
        void DisplayMainMenu() const;
        void DisplayPlayerStats(const PlayerProfile& profile) const;
        void DisplaySettingsMenu() const;
    };

} // namespace HangmanEngine

#endif // DISPLAY_MANAGER_HPP