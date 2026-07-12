#include "../include/GameEngine.hpp"
#include <iostream>
#include <conio.h>

namespace HangmanEngine {

    GameEngine::GameEngine() : 
        executionState(GameState::MAIN_MENU),
        interfaceRenderer(configSettings),
        vocabularyEngine("words.txt"),
        guessCount(0),
        gameOver(true),
        systemStatusLog("SYSTEM STATE OPERATIONAL") 
    {
        vocabularyEngine.InitializeVocabularyStream();
    }

    void GameEngine::InitializeSessionSetup() {
        guessCount = 0;
        gameOver = false;
        guessedWord = "";
        wordToGuess = vocabularyEngine.SelectTargetWord(configSettings.currentDifficulty);
        systemStatusLog = "CORE ENGINE READY. INPUT '0' TO EXIT TO ROOT MENU OR '?' FOR HINT DATA MAPS.";
    }

    void GameEngine::ExecuteLoopTick() {
        interfaceRenderer.ClearConsole();
        interfaceRenderer.PrintBoxMessage("ENGINE DESIGNED & ENGINEERED BY SYED SAAD", true, true, FG_YELLOW);
        
        interfaceRenderer.DrawVisualScaffold(guessCount);
        interfaceRenderer.DisplayRemainingAlphabet(guessedWord);
        interfaceRenderer.DisplayWordProgress(wordToGuess, guessedWord);

        if (!systemStatusLog.empty()) {
            interfaceRenderer.PrintBoxMessage(systemStatusLog, true, true, FG_MAGENTA);
        }

        std::cout << "\n" << FG_GREEN << "ENTER TARGET CHARACTER SYMBOL > " << RESET;
        std::string dynamicConsoleInput;
        std::cin >> dynamicConsoleInput;

        if (dynamicConsoleInput == "0") {
            gameOver = true;
            executionState = GameState::MAIN_MENU;
            return;
        }

        if (dynamicConsoleInput == "?") {
            sessionProfile.totalHintsUsed++;
            systemStatusLog = vocabularyEngine.AcquireAlgorithmicHint(wordToGuess, guessedWord);
            return;
        }

        ProcessUserCharacterInput(dynamicConsoleInput);
        ReevaluateSystemWinLossStates();
    }

    void GameEngine::ProcessUserCharacterInput(const std::string& processingBuffer) {
        if (processingBuffer.empty()) return;
        
        char cleanInputChar = std::tolower(processingBuffer[0]);
        
        if (!std::isalpha(cleanInputChar)) {
            systemStatusLog = "CRITICAL: SUPPLIED VALUE SINK IS NON-ALPHABETIC ELEMENT.";
            return;
        }

        if (guessedWord.find(cleanInputChar) != std::string::npos) {
            systemStatusLog = "ALERT: SELECTED VALUE ALREADY ASSIGNED IN STATE MATRICES.";
            return;
        }

        guessedWord += cleanInputChar;

        // Correct count validation matching core user framework
        if (wordToGuess.find(cleanInputChar) == std::string::npos) {
            guessCount++;
            systemStatusLog = "STATE MODIFICATION: ELEMENT FAILURE DETECTED.";
        } else {
            systemStatusLog = "STATE MODIFICATION: MATCH FOUND WITHIN ARRAY RECORD.";
        }
    }

    void GameEngine::ReevaluateSystemWinLossStates() {
        bool verifiedWinToken = true;
        for (char literal : wordToGuess) {
            if (literal != ' ' && guessedWord.find(literal) == std::string::npos) {
                verifiedWinToken = false;
                break;
            }
        }

        if (verifiedWinToken) {
            interfaceRenderer.ClearConsole();
            interfaceRenderer.DisplayHeaderBanner("VICTORY CONDITIONS SATISFIED");
            interfaceRenderer.PrintBoxMessage("SUCCESSFULLY RESOLVED WORD CHAIN: " + wordToGuess, false, false, FG_GREEN);
            interfaceRenderer.PrintBoxMessage("TOTAL PROCESSING FAULTS: " + std::to_string(guessCount), false, true, FG_GREEN);
            
            sessionProfile.totalWins++;
            sessionProfile.currentStreak++;
            if (sessionProfile.currentStreak > sessionProfile.bestStreak) {
                sessionProfile.bestStreak = sessionProfile.currentStreak;
            }
            
            gameOver = true;
            std::cout << "\n" << FG_YELLOW << "PRESS ANY KEY TO LOAD ROOT ENVIRONMENT MENU..." << RESET;
            int code = _getch();
            executionState = GameState::MAIN_MENU;
        } 
        else if (guessCount >= configSettings.maximumAllowedMisses) {
            interfaceRenderer.ClearConsole();
            interfaceRenderer.DisplayHeaderBanner("TERMINATION SEQUENCE DISPATCHED");
            interfaceRenderer.PrintBoxMessage("FAILED COMPILATION TRACE FOR TARGET: " + wordToGuess, false, true, FG_RED);
            
            sessionProfile.totalLosses++;
            sessionProfile.currentStreak = 0; // Reset active streak matrix
            
            gameOver = true;
            std::cout << "\n" << FG_YELLOW << "PRESS ANY KEY TO LOAD ROOT ENVIRONMENT MENU..." << RESET;
            int code = _getch();
            executionState = GameState::MAIN_MENU;
        }
    }

    void GameEngine::DisplayInteractiveSettingsConfig() {
        interfaceRenderer.DisplaySettingsMenu();
        std::string selectionNode;
        std::cin >> selectionNode;

        if (selectionNode == "1") {
            if (configSettings.currentDifficulty == Difficulty::EASY) 
                configSettings.currentDifficulty = Difficulty::MEDIUM;
            else if (configSettings.currentDifficulty == Difficulty::MEDIUM) 
                configSettings.currentDifficulty = Difficulty::HARD;
            else 
                configSettings.currentDifficulty = Difficulty::EASY;
        } else if (selectionNode == "2") {
            configSettings.useColors = !configSettings.useColors;
        } else if (selectionNode == "3") {
            std::cout << FG_CYAN << "SPECIFY MAX INTRUSION VALUE RATIO (5-12): " << RESET;
            int structuralConstraintInput;
            if (std::cin >> structuralConstraintInput && structuralConstraintInput >= 5 && structuralConstraintInput <= 12) {
                configSettings.maximumAllowedMisses = structuralConstraintInput;
            }
        } else if (selectionNode == "4") {
            executionState = GameState::MAIN_MENU;
        }
    }

    void GameEngine::ExecuteCoreEngineLoop() {
        while (executionState != GameState::QUIT) {
            if (executionState == GameState::MAIN_MENU) {
                interfaceRenderer.DisplayMainMenu();
                std::string controlRouteSelection;
                std::cin >> controlRouteSelection;

                if (controlRouteSelection == "1") {
                    InitializeSessionSetup();
                    executionState = GameState::PLAYING;
                } else if (controlRouteSelection == "2") {
                    executionState = GameState::STATS_BOARD;
                } else if (controlRouteSelection == "3") {
                    executionState = GameState::SETTINGS;
                } else if (controlRouteSelection == "4") {
                    executionState = GameState::QUIT;
                }
            } 
            else if (executionState == GameState::PLAYING) {
                if (!gameOver) {
                    ExecuteLoopTick();
                }
            } 
            else if (executionState == GameState::STATS_BOARD) {
                interfaceRenderer.DisplayPlayerStats(sessionProfile);
                int interactionInterceptCode = _getch();
                executionState = GameState::MAIN_MENU;
            } 
            else if (executionState == GameState::SETTINGS) {
                DisplayInteractiveSettingsConfig();
            }
        }
        
        interfaceRenderer.ClearConsole();
        std::cout << FG_MAGENTA << "SESSION PIPELINE SEVERED SUCCESSFULLY. SHUTTING DOWN ENGINE STRUCTURE." << RESET << std::endl;
    }

} // namespace HangmanEngine