#include "../include/GameEngine.hpp"
#include <iostream>
#include <conio.h>
#include <sstream>

namespace PongEngine {

    GameEngine::GameEngine() :
        executionState(GameState::MAIN_MENU),
        width(50),
        height(15),
        scorePlayer1(0),
        scorePlayer2(0),
        quitGame(false),
        namePlayer1("PLAYER 1"),
        namePlayer2("PLAYER 2")
    {
        gameBall = new Ball(width / 2, height / 2);
        paddlePlayer1 = new Paddle(1, height / 2);
        paddlePlayer2 = new Paddle(width - 2, height / 2);
        InitializeEngineConsole();
    }

    GameEngine::~GameEngine() {
        // Clean release of every dynamic class object
        delete gameBall;
        delete paddlePlayer1;
        delete paddlePlayer2;
    }

    void GameEngine::InitializeEngineConsole() {
        // Hide terminal cursor completely using Windows API to prevent system artifacting
        HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(outHandle, &cursorInfo);
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(outHandle, &cursorInfo);
    }

    void GameEngine::TriggerSystemBeep(int frequency, int duration) {
        if (settings.soundEffectsEnabled) {
            Beep(frequency, duration);
        }
    }

    void GameEngine::DrawPlayboardFrame() {
        // Set hardware cursor instantly back to coordinates (0, 0)
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });

        std::stringstream doubleBuffer;
        std::string frameColor = settings.useColors ? FG_CYAN : "";
        std::string scoreColor = settings.useColors ? FG_GREEN : "";
        std::string creditColor = settings.useColors ? FG_YELLOW : "";
        std::string resetColor = settings.useColors ? RESET : "";

        // Display Header Banner with Syed Saad Bin Irfan's Credentials
        doubleBuffer << creditColor << "=== TERMINAL PONG v2.0 | CODE ARCHITECT: " << ARCHITECT_NAME << " ===\n\n" << resetColor;

        // Render Top Border
        doubleBuffer << frameColor;
        for (int i = 0; i < width + 2; i++) {
            doubleBuffer << "\xB2";
        }
        doubleBuffer << resetColor << "\n";

        int ballX = gameBall->GetX();
        int ballY = gameBall->GetY();
        int p1X = paddlePlayer1->GetX();
        int p1Y = paddlePlayer1->GetY();
        int p2X = paddlePlayer2->GetX();
        int p2Y = paddlePlayer2->GetY();

        // Render Game Field Blocks
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0) {
                    doubleBuffer << frameColor << "\xB1" << resetColor;
                }

                if (ballX == j && ballY == i) {
                    doubleBuffer << (settings.useColors ? FG_RED : "") << "o" << resetColor;
                } 
                else if (p1X == j && (p1Y >= i && p1Y < i + 4)) {
                    doubleBuffer << (settings.useColors ? FG_GREEN : "") << "\xDB" << resetColor;
                } 
                else if (p2X == j && (p2Y >= i && p2Y < i + 4)) {
                    doubleBuffer << (settings.useColors ? FG_BLUE : "") << "\xDB" << resetColor;
                } 
                else {
                    doubleBuffer << " ";
                }

                if (j == width - 1) {
                    doubleBuffer << frameColor << "\xB1" << resetColor;
                }
            }
            doubleBuffer << "\n";
        }

        // Render Bottom Border
        doubleBuffer << frameColor;
        for (int i = 0; i < width + 2; i++) {
            doubleBuffer << "\xB2";
        }
        doubleBuffer << resetColor << "\n\n";

        // Display Dynamic Scoreboard
        int paddingSize = (width / 2) - 10;
        for (int i = 0; i < paddingSize; i++) doubleBuffer << " ";
        doubleBuffer << scoreColor << namePlayer1 << "  " << scorePlayer1 << " : " << scorePlayer2 << "  " << namePlayer2 << resetColor << "\n";

        // Push built string buffer to console screen
        std::cout << doubleBuffer.str();
    }

    void GameEngine::ProcessLiveGameInputs() {
        int p1Y = paddlePlayer1->GetY();
        int p2Y = paddlePlayer2->GetY();

        if (_kbhit()) {
            if (gameBall->GetDir() == STOP) {
                gameBall->SetRandomDirection();
            }

            int pressedKey = _getch();
            switch (pressedKey) {
                case 'w': case 'W':
                    if (p1Y - 3 > 0) paddlePlayer1->ChangeDirection(UP);
                    break;
                case 's': case 'S':
                    if (p1Y + 1 < height) paddlePlayer1->ChangeDirection(DOWN);
                    break;
                case 'i': case 'I':
                    if (executionState == GameState::PLAYING_PVP) {
                        if (p2Y - 3 > 0) paddlePlayer2->ChangeDirection(UP);
                    }
                    break;
                case 'j': case 'J':
                    if (executionState == GameState::PLAYING_PVP) {
                        if (p2Y + 1 < height) paddlePlayer2->ChangeDirection(DOWN);
                    }
                    break;
                case 'q': case 'Q':
                    quitGame = true;
                    break;
            }
        }
    }

    void GameEngine::ProcessAIComputerLogic() {
        // Runs computer tracking algorithm
        int ballY = gameBall->GetY();
        int p2Y = paddlePlayer2->GetY();
        int p2Center = p2Y - 1; // Tracks paddle central mass

        // Adjust tracking responsiveness based on game settings
        int trackingReactionProbability = (settings.aiDifficulty == Difficulty::EASY) ? 40 : 
                                          (settings.aiDifficulty == Difficulty::MEDIUM) ? 65 : 90;

        if ((std::rand() % 100) < trackingReactionProbability) {
            if (ballY < p2Center && p2Y - 3 > 0) {
                paddlePlayer2->ChangeDirection(UP);
            } 
            else if (ballY > p2Center && p2Y + 1 < height) {
                paddlePlayer2->ChangeDirection(DOWN);
            } 
            else {
                paddlePlayer2->ChangeDirection(PAUSE);
            }
        }
    }

    void GameEngine::ProcessCollisionsAndPhysics() {
        gameBall->Move();
        paddlePlayer1->Move();
        paddlePlayer2->Move();

        int ballX = gameBall->GetX();
        int ballY = gameBall->GetY();
        int p1X = paddlePlayer1->GetX();
        int p1Y = paddlePlayer1->GetY();
        int p2X = paddlePlayer2->GetX();
        int p2Y = paddlePlayer2->GetY();

        // Original collision and vector rebound physics (fully preserved and optimized)
        if (ballX == p1X + 1) {
            if (ballY == p1Y - 3) {
                gameBall->ChangeDirection(UPRIGHT);
                TriggerSystemBeep(880, 45); // Standard bounce chime
            } 
            else if (ballY == p1Y - 2 || ballY == p1Y - 1) {
                gameBall->ChangeDirection(static_cast<eDirection>((std::rand() % 3) + 1));
                TriggerSystemBeep(800, 45);
            } 
            else if (ballY == p1Y) {
                gameBall->ChangeDirection(DOWNRIGHT);
                TriggerSystemBeep(880, 45);
            }
        } 
        else if (ballX == p2X - 1) {
            if (ballY == p2Y - 3) {
                gameBall->ChangeDirection(UPLEFT);
                TriggerSystemBeep(880, 45);
            } 
            else if (ballY == p2Y - 2 || ballY == p2Y - 1) {
                gameBall->ChangeDirection(static_cast<eDirection>((std::rand() % 3) + 4));
                TriggerSystemBeep(800, 45);
            } 
            else if (ballY == p2Y) {
                gameBall->ChangeDirection(DOWNLEFT);
                TriggerSystemBeep(880, 45);
            }
        }

        // Top and bottom boundaries collisions
        if (ballY == height - 1) {
            gameBall->ChangeDirection(gameBall->GetDir() == DOWNRIGHT ? UPRIGHT : UPLEFT);
            TriggerSystemBeep(650, 40);
        } 
        else if (ballY == 0) {
            gameBall->ChangeDirection(gameBall->GetDir() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
            TriggerSystemBeep(650, 40);
        } 
        // Goal zones processing
        else if (ballX == width - 1) {
            ScorePoint(paddlePlayer1);
        } 
        else if (ballX == 0) {
            ScorePoint(paddlePlayer2);
        }

        // Keep paddles inside field borders
        if (p1Y - 4 < 0 || p1Y + 2 > height) {
            paddlePlayer1->ChangeDirection(PAUSE);
        }
        if (p2Y - 4 < 0 || p2Y + 2 > height) {
            paddlePlayer2->ChangeDirection(PAUSE);
        }
    }

    void GameEngine::ResetSessionPositions() {
        gameBall->Reset();
        paddlePlayer1->Reset();
        paddlePlayer2->Reset();
    }

    void GameEngine::ScorePoint(Paddle* winningPaddle) {
        TriggerSystemBeep(1200, 150); // Goal sound effect
        if (winningPaddle == paddlePlayer1) {
            scorePlayer1++;
        } else {
            scorePlayer2++;
        }
        ResetSessionPositions();
    }

    void GameEngine::ShowMainMenu() {
        system("cls");
        std::string textClr = settings.useColors ? FG_GREEN : "";
        std::string highlightClr = settings.useColors ? FG_CYAN : "";
        std::string resetClr = settings.useColors ? RESET : "";

        std::cout << highlightClr << "+------------------------------------------+\n";
        std::cout << "|        TERMINAL PONG arcade CORE         |\n";
        std::cout << "|      DESIGNED BY: SYED SAAD BIN IRFAN    |\n";
        std::cout << "+------------------------------------------+\n" << resetClr;
        std::cout << " 1. START LOCAL MATCH (PLAYER VS PLAYER)\n";
        std::cout << " 2. ENTER VS COMPUTER CAMPAIGN (PLAYER VS AI)\n";
        std::cout << " 3. AUDIO & VISUAL CALIBRATION (SETTINGS)\n";
        std::cout << " 4. TERMINATE CONNECTION PIPELINE (QUIT)\n\n";
        std::cout << textClr << "SELECT OPERATIONAL VECTOR NODE > " << resetClr;

        std::string option;
        std::cin >> option;

        if (option == "1") {
            InitializeGameMatch(false);
        } else if (option == "2") {
            InitializeGameMatch(true);
        } else if (option == "3") {
            executionState = GameState::SETTINGS;
        } else if (option == "4") {
            executionState = GameState::QUIT;
        }
    }

    void GameEngine::ShowSettingsMenu() {
        system("cls");
        std::string highlightClr = settings.useColors ? FG_CYAN : "";
        std::string statusClr = settings.useColors ? FG_GREEN : "";
        std::string resetClr = settings.useColors ? RESET : "";

        std::cout << highlightClr << "=== CALIBRATION CONSOLE ===\n\n" << resetClr;
        std::cout << "1. TOGGLE SOUND MATRIX [" << statusClr << (settings.soundEffectsEnabled ? "ENABLED" : "DISABLED") << resetClr << "]\n";
        std::cout << "2. TOGGLE ANSI COLOR LAYERS [" << statusClr << (settings.useColors ? "ENABLED" : "DISABLED") << resetClr << "]\n";
        std::cout << "3. SCALE COMPUTER CPU COMPETENCY [" << statusClr << (settings.aiDifficulty == Difficulty::EASY ? "EASY" : settings.aiDifficulty == Difficulty::MEDIUM ? "MEDIUM" : "HARD") << resetClr << "]\n";
        std::cout << "4. MODIFY MATCH POINT TARGET Limit [" << statusClr << settings.maxWinningScore << " POINTS" << resetClr << "]\n";
        std::cout << "5. RETURN TO MAIN MENU CONSOLE\n\n";
        std::cout << highlightClr << "SELECT SETTINGS NODE > " << resetClr;

        std::string option;
        std::cin >> option;

        if (option == "1") {
            settings.soundEffectsEnabled = !settings.soundEffectsEnabled;
        } else if (option == "2") {
            settings.useColors = !settings.useColors;
        } else if (option == "3") {
            if (settings.aiDifficulty == Difficulty::EASY) settings.aiDifficulty = Difficulty::MEDIUM;
            else if (settings.aiDifficulty == Difficulty::MEDIUM) settings.aiDifficulty = Difficulty::HARD;
            else settings.aiDifficulty = Difficulty::EASY;
        } else if (option == "4") {
            std::cout << "SET MATCH TARGET VALUE (3-15): ";
            int scoreLimit;
            if (std::cin >> scoreLimit && scoreLimit >= 3 && scoreLimit <= 15) {
                settings.maxWinningScore = scoreLimit;
            }
        } else if (option == "5") {
            executionState = GameState::MAIN_MENU;
        }
    }

    void GameEngine::InitializeGameMatch(bool playAgainstAI) {
        system("cls");
        scorePlayer1 = 0;
        scorePlayer2 = 0;
        quitGame = false;
        ResetSessionPositions();

        std::cout << "ENTER REGISTERED IDENTITY FOR PLAYER 1: ";
        std::cin >> namePlayer1;
        
        if (playAgainstAI) {
            namePlayer2 = "CPU CONTROLLER";
            executionState = GameState::PLAYING_PVAI;
        } else {
            std::cout << "ENTER REGISTERED IDENTITY FOR PLAYER 2: ";
            std::cin >> namePlayer2;
            executionState = GameState::PLAYING_PVP;
        }
        
        // Dynamic game launch countdown
        for (int i = 3; i > 0; --i) {
            system("cls");
            std::cout << "\n\n\n\t\tCOMPILING INTERFACES IN... " << i << "\n";
            TriggerSystemBeep(500, 200);
            Sleep(800);
        }
        system("cls");
    }

    void GameEngine::ExecuteMainLoop() {
        while (executionState != GameState::QUIT) {
            if (executionState == GameState::MAIN_MENU) {
                ShowMainMenu();
            } 
            else if (executionState == GameState::SETTINGS) {
                ShowSettingsMenu();
            } 
            else if (executionState == GameState::PLAYING_PVP || executionState == GameState::PLAYING_PVAI) {
                DrawPlayboardFrame();
                ProcessLiveGameInputs();
                
                if (executionState == GameState::PLAYING_PVAI) {
                    ProcessAIComputerLogic();
                }
                
                ProcessCollisionsAndPhysics();
                Sleep(settings.gameSpeedMs); // Limits execution speed to maintain uniform playability

                // Assess ultimate end-game criteria
                if (scorePlayer1 >= settings.maxWinningScore || scorePlayer2 >= settings.maxWinningScore || quitGame) {
                    system("cls");
                    std::cout << (settings.useColors ? FG_YELLOW : "") << "=== TOURNAMENT CONCLUDED ===\n\n" << RESET;
                    if (scorePlayer1 != scorePlayer2) {
                        std::cout << (scorePlayer1 > scorePlayer2 ? namePlayer1 : namePlayer2) << " SECURES THE MATCH VICTORY!\n";
                    } else {
                        std::cout << "THE CURRENT COMPETITION ENDS IN A MATCH DRAW.\n";
                    }
                    std::cout << "\nFINAL OUTCOME SCORE: " << scorePlayer1 << " - " << scorePlayer2 << "\n";
                    TriggerSystemBeep(1500, 350);
                    
                    std::cout << "\nPRESS ANY KEY TO TRANSITION TO THE MAIN MENU CONSOLE...";
                    _getch();
                    executionState = GameState::MAIN_MENU;
                }
            }
        }

        system("cls");
        std::cout << "SHUTTING DOWN SYSTEM SYSTEMS PIPELINE safely..." << std::endl;
    }

} // namespace PongEngine