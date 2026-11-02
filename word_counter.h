#ifndef WORD_COUNTER_H
#define WORD_COUNTER_H

#include <string>
#include <unordered_map>
#include <vector>

struct WordStat {
    std::string word;
    int frequency;
    double percentage;
};

class WordCounter {
private:
    std::unordered_map<std::string, int> wordsCounter;
    int totalWords = 0;

    static bool isWordValid(char symbol);

public:
    void processLine(const std::string& line);

    [[nodiscard]]
    std::vector<WordStat> getStatistics() const;
};

#endif