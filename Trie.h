#ifndef OOP_LAB1_TRIE_TRIE_H
#define OOP_LAB1_TRIE_TRIE_H
#include <cstddef>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

using size_type = std::size_t;

class Trie {
private:
    struct Node {
        std::map<char, std::unique_ptr<Node>> children;
        bool isEnd = false;
        size_type wordContainsCounter = 0;
    };
    std::unique_ptr<Node> root = std::make_unique<Node>();
    size_type wordCounter = 0;
public:
    Trie();
    ~Trie();
    void insert(std::string_view word);
    bool contains(std::string_view word) const;
    bool erase (std::string_view word);
    size_type prefixCount(std::string_view pref) const;
    void collectWords(const Node* node, std::string& currentWord, std::vector<std::string>& result, size_type limit) const;
    std::vector<std::string> wordsWithPrefix(std::string_view pref, size_type limit = 0) const;
    size_type size() const;
    bool empty() const;
    void clear();
    std::unique_ptr<Trie::Node> cloneNode(const Node* node) const;
    Trie(const Trie& other);
    Trie(Trie&& other) noexcept;
    Trie& operator=(const Trie& other);
    Trie& operator=(Trie&& other) noexcept;
    bool compareNodes(const Node* a, const Node* b) const;
    bool operator==(const Trie& other) const;
    bool operator!=(const Trie& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Trie& trie);
};










#endif //OOP_LAB1_TRIE_TRIE_H