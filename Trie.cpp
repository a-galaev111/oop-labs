#include "Trie.h"

#include <string>
#include <map>

bool Trie::contains(std::string_view word) const {
    const Node *current = root.get();
    if (current == nullptr) {
        return false;
    }
    for (char c: word) {
        auto it = current->children.find(c);
        if (it != current->children.end()) {
            current = it->second.get();
        } else return false;
    }
    return current->isEnd;
}

void Trie::insert(std::string_view word) {
    if (contains(word)) return;
    if (root == nullptr) {
        root = std::make_unique<Node>();
    }
    Node *current = root.get();

    for (char c: word) {
        auto it = current->children.find(c);
        if (it != current->children.end()) {
            current = it->second.get();
        } else {
            current->children[c] = std::make_unique<Node>();
            current = current->children[c].get();
        }
        current->wordContainsCounter++;
    }
    current->isEnd = true;
    wordCounter++;
}

size_type Trie::size() const {
    return wordCounter;
}

bool Trie::empty() const {
    return wordCounter == 0;
}

size_type Trie::prefixCount(std::string_view pref) const {
    if (pref == "") return wordCounter;
    if (root == nullptr) return 0;
    const Node *current = root.get();

    for (char c: pref) {
        auto it = current->children.find(c);
        if (it != current->children.end()) {
            current = it->second.get();
        } else return 0;
    }
    return current->wordContainsCounter;
}

void Trie::collectWords(const Node *node, std::string &currentWord, std::vector<std::string> &result,
                        size_type limit) const {
    if (node->isEnd) result.push_back(currentWord);
    if (limit != 0 && result.size() >= limit) return;
    for (const auto &child: node->children) {
        if (limit != 0 && result.size() >= limit) {
            return;
        }
        currentWord.push_back(child.first);
        collectWords(child.second.get(), currentWord, result, limit);
        currentWord.pop_back();
    }
}

std::vector<std::string> Trie::wordsWithPrefix(std::string_view pref, size_type limit) const {
    std::vector<std::string> result;
    if (root == nullptr) return result;
    const Node *current = root.get();

    for (char c: pref) {
        auto it = current->children.find(c);
        if (it != current->children.end()) {
            current = it->second.get();
        } else return result;
    }
    std::string currentWord(pref);
    collectWords(current, currentWord, result, limit);
    return result;
}

bool Trie::erase(std::string_view word) {
    if (!contains(word)) return false;
    Node *current = root.get();
    for (char c: word) {
        auto it = current->children.find(c);
        Node *child = it->second.get();
        if (child->wordContainsCounter == 1) {
            current->children.erase(it);;
            wordCounter--;
            return true;
        } else {
            child->wordContainsCounter--;
            current = child;
        }
    }
    current->isEnd = false;
    wordCounter--;
    return true;
}

void Trie::clear() {
    if (root == nullptr) {
        wordCounter = 0;
        return;
    }
    Node *current = root.get();
    current->children.clear();
    wordCounter = 0;
    current->isEnd = false;
    return;
}


std::unique_ptr<Trie::Node> Trie::cloneNode(const Node *node) const {
    if (node == nullptr) return nullptr;
    std::unique_ptr<Node> newNode = std::make_unique<Node>();
    newNode->isEnd = node->isEnd;
    newNode->wordContainsCounter = node->wordContainsCounter;
    for (const auto &child: node->children) {
        newNode->children[child.first] = cloneNode(child.second.get());
    }
    return newNode;
}

Trie::Trie(const Trie &other) {
    if (other.root == nullptr) return;
    root = cloneNode(other.root.get());
    wordCounter = other.wordCounter;
}

Trie::Trie(Trie &&other) noexcept
    : root(std::move(other.root)),
      wordCounter(other.wordCounter) {
    other.wordCounter = 0;
}

Trie &Trie::operator=(const Trie &other) {
    Trie temp(other);
    root = std::move(temp.root);
    wordCounter = temp.wordCounter;
    return *this;
}

Trie &Trie::operator=(Trie &&other) noexcept {
    if (this == &other) return *this;
    root = std::move(other.root);
    wordCounter = other.wordCounter;
    other.wordCounter = 0;
    return *this;
}

bool Trie::compareNodes(const Node* a, const Node* b) const {
    if (a == nullptr && b == nullptr) return true;
    if (a == nullptr || b == nullptr) return false;

    if (a->isEnd != b->isEnd) return false;

    if (a->children.size() != b->children.size()) return false;

    for (const auto& childA : a->children) {
        auto it = b->children.find(childA.first);

        if (it == b->children.end()) return false;

        if (!compareNodes(childA.second.get(), it->second.get())) {
            return false;
        }
    }

    return true;
}

bool Trie::operator==(const Trie& other) const {
    if (wordCounter != other.wordCounter) return false;
    if (wordCounter == 0) return true;
    return compareNodes(root.get(), other.root.get());
}

bool Trie::operator!=(const Trie& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Trie& trie) {
    auto words = trie.wordsWithPrefix("");
    for (const auto& word : words) {
        os<<word<<'\n';
    }
    return os;
}

Trie::Trie() = default;

Trie::~Trie() = default;