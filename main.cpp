#include "csv_writer.h"
#include "text_reader.h"
#include "word_counter.h"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    constexpr int expected_argument_count = 3; //NOLINT

    if (argc != expected_argument_count) {
        std::cerr << "Error: invalid input format\n";
        return 1;
    }

    const std::string inputFile = argv[1]; //NOLINT
    const std::string outputFile = argv[2]; //NOLINT

    TextReader reader;
    if (!reader.openFile(inputFile)) {
        std::cerr << "Failed to open input file\n";
        return 1;
    }
    WordCounter counter;
    std::string line;

    while (reader.readLine(line)) {
        counter.processLine(line);
    }
    const std::vector<WordStat> statistics = counter.getStatistics(); //NOLINT

    const std::string csvHeader = "Word,Frequency,Frequency (%)"; //NOLINT
    if (!CsvWriter::writeCsv(outputFile, statistics, csvHeader)) {
        std::cerr << "Failed to open output file\n";
        return 1;
    }
    return 0;
}
