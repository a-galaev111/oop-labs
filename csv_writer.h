#include <map>
#include <string>
#include <utility>

class CsvWriter {
private:
    static bool compareWords(const std::pair<std::string, int> &first, const std::pair<std::string, int> &second);

public:
    void writeCsv(const std::string &fileName, const std::map<std::string, int> &wordsCounter, int totalWords);
};
