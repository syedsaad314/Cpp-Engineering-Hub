#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "PongConfig.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include <Windows.h>
#include <string>

namespace PongEngine {

    class GameEngine {
    private:
        GameState executionState;
        EngineSettings settings;
        
        int width;
        int height;
        int scorePlayer1;
        int scorePlayer2;
        bool quitGame;

        Ball* gameBall;
        Paddle* paddlePlayer1;
        Paddle* paddlePlayer2;

        std::string namePlayer1;
        std::string namePlayer2;

        void InitializeEngineConsole();
        void TriggerSystemBeep(int frequency, int duration);
        void DrawPlayboardFrame();
        void ProcessLiveGameInputs();
        void ProcessAIComputerLogic();
        void ProcessCollisionsAndPhysics();
        void ResetSessionPositions();
        void ScorePoint(Paddle* winningPaddle);
        void ShowMainMenu();
        void ShowSettingsMenu();
        void InitializeGameMatch(bool playAgainstAI);

    public:
        GameEngine();
        ~GameEngine();
        
        void ExecuteMainLoop();
    };

} // namespace PongEngine

#endif // GAME_ENGINE_HPP