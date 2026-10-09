#include <list>
#include <string>
#include <map>

class WordCounter
{
private:
    std::map<std::string, int> words_counter;
    int total_words = 0;

public:
    void countWords(const std::list<std::string>& text);
    const std::map<std::string, int>& getWordsCounter() const;
    int getTotalWords() const;
};