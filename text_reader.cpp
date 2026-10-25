#include "text_reader.h"
#include <fstream>
#include <string>


bool TextReader::openFile(const std::string& fileName) {
    input.open(fileName);
    return input.is_open();
}

bool TextReader::readLine(std::string& line) {
    return static_cast<bool>(std::getline(input, line));
}