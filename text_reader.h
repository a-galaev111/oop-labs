#include <fstream>
#include <string>


class TextReader {
private:
    std::ifstream input;
public:
    bool openFile(const std::string& fileName);
    bool readLine(std::string& line);
};