#include "word_counter.h"

#include <string>
#include <vector>

class CsvWriter {


public:
    [[nodiscard]]
    static bool writeCsv(const std::string &fileName, const std::vector<WordStat> &statistics, const std::string& header);
};
