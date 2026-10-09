#include <string>
#include <list>


class TextReader {
private:
    std::list<std::string> text;
public:
    void readFile(const std::string& file_name);
    const std::list<std::string>& getText() const;
};