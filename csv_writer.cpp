#include "csv_writer.h"
#include <fstream>
#include <list>
#include <utility>


bool CsvWriter::compareWords(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second;
}


void CsvWriter::writeCsv(const std::string &file_name, const std::map<std::string, int> &words_counter, int total_words) {
    std::ofstream output;
    output.open(file_name);
    std::list<std::pair<std::string, int>> sorted_words;

    for (const auto& element : words_counter) {
        sorted_words.push_back(element);
    }
    sorted_words.sort(compareWords);

    output<<"Word,Frequency,Frequency (%)\n";
    if (total_words != 0){
        for (const auto& word_info : sorted_words) {
            float percentage = 0;
            percentage = word_info.second / (float)total_words * 100.0;
            output << word_info.first << "," << word_info.second <<"," << percentage<< "\n";
        }
    }
}
