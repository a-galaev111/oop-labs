#include "text_reader.h"
#include <fstream>


void TextReader::readFile(const std::string &file_name) {
    std::ifstream input;
    input.open(file_name);
    if (!input.is_open()) {
        return;
    }
    std::string line;

    while (std::getline(input, line)) {
        text.push_back(line);
    }
}


const std::list<std::string>& TextReader::getText() const {
    return text;
}