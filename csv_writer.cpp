#include "csv_writer.h"
#include "word_counter.h"

#include <fstream>
#include <string>
#include <vector>


bool CsvWriter::writeCsv(const std::string &fileName, const std::vector<WordStat> &statistics,
                         const std::string &header) {
    std::ofstream output;
    output.open(fileName);
    if (!output.is_open()) {
        return false;
    }
    output << header << '\n';
    for (const WordStat &wordStat: statistics) {
        output << wordStat.word << ',' << wordStat.frequency << ',' << wordStat.percentage << '\n';
    }

    return true;
}
