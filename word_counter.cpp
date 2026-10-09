#include "word_counter.h"
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>


void WordCounter::countWords(const std::list<std::string>& text) {
    for (const std::string &line: text) {
        std::string word;
        for (int i = 0; i < line.length(); i++) {
            char symbol = line[i];
            if (std::isalnum(symbol)) {
                word += symbol;
            } else {
                if (!word.empty()) {
                    words_counter[word]++;
                    total_words++;
                    word.clear();
                }
            }
        }
        if (!word.empty()){
            words_counter[word]++;
            total_words++;
        }
    }
}

const std::map<std::string, int>& WordCounter::getWordsCounter() const {
    return words_counter;
}

int WordCounter::getTotalWords() const{
    return total_words;
}
