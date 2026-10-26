#include "word_counter.h"

#include <algorithm>
#include <cctype>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

bool WordCounter::isWordValid(char symbol) {
    return std::isalnum(static_cast<unsigned char>(symbol)) != 0;
}

void WordCounter::processLine(const std::string &line) {
    std::string word;
    for (const char symbol: line) { //NOLINT
        if (isWordValid(symbol)) {
            word += symbol;
        } else {
            if (!word.empty()) {
                wordsCounter[word]++;
                totalWords++;
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        wordsCounter[word]++;
        totalWords++;
    }
}

std::vector<WordStat> WordCounter::getStatistics() const {
    std::vector<WordStat> statistics;
    for (const auto &element: wordsCounter) {
        const double percentage = static_cast<double>(element.second) / static_cast<double>(totalWords) * 100.0; //NOLINT
        statistics.emplace_back(WordStat{.word = element.first, .frequency = element.second, .percentage = percentage});
    }
    std::ranges::sort(statistics, std::greater{}, &WordStat::frequency);
    return statistics;
}
