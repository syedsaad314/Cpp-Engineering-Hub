#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "HangmanConfig.hpp"
#include "DisplayManager.hpp"
#include "WordManager.hpp"

namespace HangmanEngine {

    class GameEngine {
    private:
        GameState executionState;
        GameSettings configSettings;
        PlayerProfile sessionProfile;
        
        DisplayManager interfaceRenderer;
        WordManager vocabularyEngine;

        // Current Live Loop Variables matching user configuration rules
        int guessCount;
        bool gameOver;
        std::string guessedWord;
        std::string wordToGuess;
        std::string systemStatusLog;

        void InitializeSessionSetup();
        void ExecuteLoopTick();
        void ProcessUserCharacterInput(const std::string& processingBuffer);
        void ReevaluateSystemWinLossStates();
        void DisplayInteractiveSettingsConfig();

    public:
        GameEngine();
        void ExecuteCoreEngineLoop();
    };

} // namespace HangmanEngine

#endif // GAME_ENGINE_HPP