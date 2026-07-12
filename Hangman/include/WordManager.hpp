#ifndef WORD_MANAGER_HPP
#define WORD_MANAGER_HPP

#include "HangmanConfig.hpp"
#include <string>
#include <vector>

namespace HangmanEngine {

    class WordManager {
    private:
        std::vector<std::string> centralVocabularyBank;
        std::string vocabularyFilePath;
        void SeedSystemFallbackWords();

    public:
        explicit WordManager(std::string path = "words.txt");
        
        bool InitializeVocabularyStream();
        std::string SelectTargetWord(Difficulty level);
        std::string AcquireAlgorithmicHint(const std::string& targetWord, const std::string& historyState) const;
    };

} // namespace HangmanEngine

#endif // WORD_MANAGER_HPP