#include "../include/WordManager.hpp"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

namespace HangmanEngine {

    WordManager::WordManager(std::string path) : vocabularyFilePath(path) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    void WordManager::SeedSystemFallbackWords() {
        // Safe standard dataset array in case files are blocked
        centralVocabularyBank = {
            "polymorphism", "encapsulation", "inheritance", "pointer", 
            "compilation", "repository", "architecture", "interface", 
            "debugger", "memory", "allocation", "destructor", "template"
        };
    }

    bool WordManager::InitializeVocabularyStream() {
        centralVocabularyBank.clear();
        std::ifstream wordFileStream(vocabularyFilePath);
        
        if (!wordFileStream.is_open()) {
            SeedSystemFallbackWords();
            return false;
        }

        std::string placeholder;
        while (std::getline(wordFileStream, placeholder)) {
            // Data scrubbing logic
            placeholder.erase(std::remove_if(placeholder.begin(), placeholder.end(), ::isspace), placeholder.end());
            if (!placeholder.empty()) {
                std::transform(placeholder.begin(), placeholder.end(), placeholder.begin(), ::tolower);
                centralVocabularyBank.push_back(placeholder);
            }
        }
        
        wordFileStream.close();
        if (centralVocabularyBank.empty()) {
            SeedSystemFallbackWords();
        }
        return true;
    }

    std::string WordManager::SelectTargetWord(Difficulty level) {
        if (centralVocabularyBank.empty()) {
            InitializeVocabularyStream();
        }

        std::vector<std::string> operationalSubset;
        for (const auto& entry : centralVocabularyBank) {
            if (level == Difficulty::EASY && entry.length() <= 5) {
                operationalSubset.push_back(entry);
            } else if (level == Difficulty::MEDIUM && entry.length() > 5 && entry.length() <= 9) {
                operationalSubset.push_back(entry);
            } else if (level == Difficulty::HARD && entry.length() > 9) {
                operationalSubset.push_back(entry);
            }
        }

        // Fallback protection layer
        if (operationalSubset.empty()) {
            operationalSubset = centralVocabularyBank;
        }

        return operationalSubset.at(std::rand() % operationalSubset.size());
    }

    std::string WordManager::AcquireAlgorithmicHint(const std::string& targetWord, const std::string& historyState) const {
        for (char character : targetWord) {
            if (historyState.find(character) == std::string::npos) {
                std::string resultHint = "SYSTEM COMPILER HINT: TRY EXECUTING THE KEY NODE '";
                resultHint += std::toupper(character);
                resultHint += "'";
                return resultHint;
            }
        }
        return "NO ADDITIONAL HINTS RESIDING IN VECTOR BUFFERS.";
    }

} // namespace HangmanEngine