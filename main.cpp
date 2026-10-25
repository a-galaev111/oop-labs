#include "csv_writer.h"
#include "text_reader.h"
#include "word_counter.h"

#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    constexpr int EXPECTED_ARGUMENT_COUNT = 3;

    if (argc != EXPECTED_ARGUMENT_COUNT) {
        std::cerr << "Error: invalid input format\n";
        return 1;
    }

    const std::string INPUT_FILE = *std::next(argv);
    const std::string OUTPUT_FILE = *std::next(argv, 2);

    TextReader reader;
    if (!reader.openFile(INPUT_FILE)) {
        std::cerr << "Failed to open input file\n";
        return 1;
    }
    WordCounter counter;
    std::string line;

    while (reader.readLine(line)) {
        counter.processLine(line);
    }
    const std::vector<WordStat> STATISTICS = counter.getStatistics();

    const std::string CSV_HEADER = "Word,Frequency,Frequency (%)";
    if (!CsvWriter::writeCsv(OUTPUT_FILE, STATISTICS, CSV_HEADER)) {
        std::cerr << "Failed to open output file\n";
        return 1;
    }
    return 0;
}
