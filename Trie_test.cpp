#include <gtest/gtest.h>
#include "Trie.h"

#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>


TEST(TrieTest, EmptyTrie) {
    Trie trie;

    EXPECT_TRUE(trie.empty());
    EXPECT_EQ(trie.size(), 0);
    EXPECT_FALSE(trie.contains("cat"));
}

TEST(TrieTest, InsertOneWord) {
    Trie trie;
    trie.insert("cat");

    EXPECT_TRUE(trie.contains("cat"));
    EXPECT_EQ(trie.size(), 1);
    EXPECT_FALSE(trie.empty());
}

TEST(TrieTest, InsertDuplicate) {
    Trie trie;
    trie.insert("cat");
    trie.insert("cat");

    EXPECT_TRUE(trie.contains("cat"));
    EXPECT_EQ(trie.size(), 1);
    EXPECT_EQ(trie.prefixCount("ca"), 1);
}

TEST(TrieTest, InsertMultipleWords) {
    Trie trie;
    trie.insert("cat");
    trie.insert("car");
    trie.insert("dog");

    EXPECT_EQ(trie.size(), 3);
    EXPECT_TRUE(trie.contains("cat"));
    EXPECT_TRUE(trie.contains("car"));
    EXPECT_TRUE(trie.contains("dog"));
    EXPECT_FALSE(trie.contains("bird"));
}

TEST(TrieTest, InsertEmptyString) {
    Trie trie;
    trie.insert("");
    trie.insert("cat");
    trie.insert("");

    EXPECT_TRUE(trie.contains(""));
    EXPECT_TRUE(trie.contains("cat"));
    EXPECT_EQ(trie.size(), 2);
    EXPECT_EQ(trie.prefixCount(""), 2);
}

TEST(TrieTest, PrefixIsNotAutomaticallyAWord) {
    Trie trie;
    trie.insert("cart");

    EXPECT_TRUE(trie.contains("cart"));
    EXPECT_FALSE(trie.contains("car"));
    EXPECT_FALSE(trie.contains("ca"));
}

TEST(TrieTest, ContainsIsCaseSensitive) {
    Trie trie;
    trie.insert("Cat");

    EXPECT_TRUE(trie.contains("Cat"));
    EXPECT_FALSE(trie.contains("cat"));
}


TEST(TrieTest, PrefixCount) {
    Trie trie;
    trie.insert("car");
    trie.insert("card");
    trie.insert("cat");
    trie.insert("dog");

    EXPECT_EQ(trie.prefixCount("ca"), 3);
    EXPECT_EQ(trie.prefixCount("car"), 2);
    EXPECT_EQ(trie.prefixCount("card"), 1);
    EXPECT_EQ(trie.prefixCount("dog"), 1);
    EXPECT_EQ(trie.prefixCount("do"), 1);
    EXPECT_EQ(trie.prefixCount("xyz"), 0);
    EXPECT_EQ(trie.prefixCount(""), 4);
}

TEST(TrieTest, PrefixCountAfterDuplicateInsertion) {
    Trie trie;
    trie.insert("car");
    trie.insert("car");
    trie.insert("cart");

    EXPECT_EQ(trie.prefixCount("car"), 2);
    EXPECT_EQ(trie.size(), 2);
}

TEST(TrieTest, WordsWithPrefixReturnsSortedWords) {
    Trie trie;
    trie.insert("cat");
    trie.insert("dog");
    trie.insert("car");
    trie.insert("cart");

    const std::vector<std::string> expectedAll = {"car", "cart", "cat", "dog"};
    const std::vector<std::string> expectedCa = {"car", "cart", "cat"};

    EXPECT_EQ(trie.wordsWithPrefix(""), expectedAll);
    EXPECT_EQ(trie.wordsWithPrefix("ca"), expectedCa);
}

TEST(TrieTest, WordsWithPrefixLimit) {
    Trie trie;
    trie.insert("cat");
    trie.insert("car");
    trie.insert("cart");
    trie.insert("dog");

    const std::vector<std::string> firstTwo = {"car", "cart"};
    const std::vector<std::string> allCa = {"car", "cart", "cat"};

    EXPECT_EQ(trie.wordsWithPrefix("ca", 2), firstTwo);
    EXPECT_EQ(trie.wordsWithPrefix("ca", 0), allCa);
    EXPECT_EQ(trie.wordsWithPrefix("ca", 100), allCa);
}

TEST(TrieTest, WordsWithPrefixNoMatches) {
    Trie trie;
    trie.insert("cat");

    EXPECT_TRUE(trie.wordsWithPrefix("dog").empty());
    EXPECT_TRUE(trie.wordsWithPrefix("cats").empty());
}

TEST(TrieTest, WordsWithPrefixIncludesEmptyString) {
    Trie trie;
    trie.insert("");
    trie.insert("a");
    trie.insert("ab");

    const std::vector<std::string> expected = {"", "a", "ab"};
    EXPECT_EQ(trie.wordsWithPrefix(""), expected);
    EXPECT_EQ(trie.wordsWithPrefix("", 1), (std::vector<std::string>{""}));
}

TEST(TrieTest, InsertFromStringView) {
    Trie trie;
    const std::string source = "cartoon";
    const std::string_view firstThree(source.data(), 3);
    trie.insert(firstThree);

    EXPECT_TRUE(trie.contains("car"));
    EXPECT_FALSE(trie.contains("cartoon"));
    EXPECT_EQ(trie.size(), 1);
}


TEST(TrieTest, EraseMissingWord) {
    Trie trie;
    trie.insert("cat");

    EXPECT_FALSE(trie.erase("dog"));
    EXPECT_FALSE(trie.erase("ca"));
    EXPECT_EQ(trie.size(), 1);
    EXPECT_TRUE(trie.contains("cat"));
}

TEST(TrieTest, EraseExistingWord) {
    Trie trie;
    trie.insert("cat");
    trie.insert("dog");

    EXPECT_TRUE(trie.erase("cat"));
    EXPECT_FALSE(trie.contains("cat"));
    EXPECT_TRUE(trie.contains("dog"));
    EXPECT_EQ(trie.size(), 1);
    EXPECT_FALSE(trie.erase("cat"));
}

TEST(TrieTest, ErasePrefixKeepsLongerWords) {
    Trie trie;
    trie.insert("car");
    trie.insert("card");
    trie.insert("cart");

    EXPECT_TRUE(trie.erase("car"));
    EXPECT_FALSE(trie.contains("car"));
    EXPECT_TRUE(trie.contains("card"));
    EXPECT_TRUE(trie.contains("cart"));
    EXPECT_EQ(trie.prefixCount("car"), 2);
}

TEST(TrieTest, EraseLongerWordKeepsPrefix) {
    Trie trie;
    trie.insert("car");
    trie.insert("cart");

    EXPECT_TRUE(trie.erase("cart"));
    EXPECT_TRUE(trie.contains("car"));
    EXPECT_FALSE(trie.contains("cart"));
    EXPECT_EQ(trie.prefixCount("car"), 1);
}

TEST(TrieTest, EraseSharedBranch) {
    Trie trie;
    trie.insert("car");
    trie.insert("cat");
    trie.insert("dog");

    EXPECT_TRUE(trie.erase("car"));
    EXPECT_TRUE(trie.contains("cat"));
    EXPECT_TRUE(trie.contains("dog"));
    EXPECT_EQ(trie.prefixCount("ca"), 1);
    EXPECT_EQ(trie.size(), 2);
}

TEST(TrieTest, EraseEmptyString) {
    Trie trie;
    trie.insert("");
    trie.insert("cat");

    EXPECT_TRUE(trie.erase(""));
    EXPECT_FALSE(trie.contains(""));
    EXPECT_TRUE(trie.contains("cat"));
    EXPECT_EQ(trie.size(), 1);
}

TEST(TrieTest, EraseLastWordAndReinsert) {
    Trie trie;
    trie.insert("cat");
    EXPECT_TRUE(trie.erase("cat"));

    EXPECT_TRUE(trie.empty());
    EXPECT_EQ(trie.prefixCount("c"), 0);
    EXPECT_TRUE(trie.wordsWithPrefix("").empty());

    trie.insert("cat");
    EXPECT_TRUE(trie.contains("cat"));
    EXPECT_EQ(trie.size(), 1);
}


TEST(TrieTest, ClearRemovesAllWords) {
    Trie trie;
    trie.insert("");
    trie.insert("cat");
    trie.insert("dog");
    trie.clear();

    EXPECT_TRUE(trie.empty());
    EXPECT_EQ(trie.size(), 0);
    EXPECT_FALSE(trie.contains(""));
    EXPECT_FALSE(trie.contains("cat"));
    EXPECT_EQ(trie.prefixCount("ca"), 0);
    EXPECT_TRUE(trie.wordsWithPrefix("").empty());

    trie.insert("new");
    EXPECT_TRUE(trie.contains("new"));
}

TEST(TrieTest, ClearEmptyTrieTwice) {
    Trie trie;
    trie.clear();
    trie.clear();

    EXPECT_TRUE(trie.empty());
    EXPECT_EQ(trie.size(), 0);
}


TEST(TrieTest, CopyConstructorMakesIndependentCopy) {
    Trie original;
    original.insert("cat");
    original.insert("car");

    Trie copy(original);
    EXPECT_TRUE(copy == original);

    copy.erase("cat");
    copy.insert("dog");

    EXPECT_TRUE(original.contains("cat"));
    EXPECT_FALSE(original.contains("dog"));
    EXPECT_FALSE(copy.contains("cat"));
    EXPECT_TRUE(copy.contains("dog"));
}

TEST(TrieTest, CopyAssignmentReplacesOldContent) {
    Trie source;
    source.insert("cat");
    source.insert("car");

    Trie target;
    target.insert("dog");
    target = source;

    EXPECT_TRUE(target == source);
    EXPECT_FALSE(target.contains("dog"));

    source.insert("new");
    EXPECT_FALSE(target.contains("new"));
}

TEST(TrieTest, CopyAssignmentToSelf) {
    Trie trie;
    trie.insert("cat");
    trie.insert("dog");

    trie = trie;

    EXPECT_TRUE(trie.contains("cat"));
    EXPECT_TRUE(trie.contains("dog"));
    EXPECT_EQ(trie.size(), 2);
}


TEST(TrieTest, MoveConstructorTransfersWords) {
    Trie source;
    source.insert("cat");
    source.insert("dog");

    Trie target(std::move(source));

    EXPECT_EQ(target.size(), 2);
    EXPECT_TRUE(target.contains("cat"));
    EXPECT_TRUE(target.contains("dog"));
    EXPECT_TRUE(source.empty());

    source.insert("new");
    EXPECT_TRUE(source.contains("new"));
}

TEST(TrieTest, MoveAssignmentReplacesOldContent) {
    Trie source;
    source.insert("cat");

    Trie target;
    target.insert("dog");
    target = std::move(source);

    EXPECT_TRUE(target.contains("cat"));
    EXPECT_FALSE(target.contains("dog"));
    EXPECT_EQ(target.size(), 1);
    EXPECT_TRUE(source.empty());

    source.insert("new");
    EXPECT_TRUE(source.contains("new"));
}

TEST(TrieTest, MoveAssignmentToSelf) {
    Trie trie;
    trie.insert("cat");

    trie = std::move(trie);

    EXPECT_TRUE(trie.contains("cat"));
    EXPECT_EQ(trie.size(), 1);
}


TEST(TrieTest, EqualWordsInsertedInDifferentOrder) {
    Trie a;
    a.insert("cat");
    a.insert("car");

    Trie b;
    b.insert("car");
    b.insert("cat");

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(TrieTest, DifferentWordsWithSameSizeAreNotEqual) {
    Trie a;
    a.insert("cat");

    Trie b;
    b.insert("dog");

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(TrieTest, EmptyMovedFromTrieEqualsNewEmptyTrie) {
    Trie source;
    source.insert("cat");
    Trie destination(std::move(source));
    Trie empty;

    EXPECT_TRUE(source == empty);
    EXPECT_FALSE(source != empty);
    EXPECT_TRUE(destination != empty);
}


TEST(TrieTest, OutputInAsciiAlphabeticalOrder) {
    Trie trie;
    trie.insert("dog");
    trie.insert("cat");
    trie.insert("car");

    std::ostringstream out;
    out << trie;

    EXPECT_EQ(out.str(), "car\ncat\ndog\n");
}

TEST(TrieTest, OutputEmptyTrieAndEmptyString) {
    Trie trie;
    std::ostringstream out;
    out << trie;
    EXPECT_EQ(out.str(), "");

    trie.insert("");
    std::ostringstream outWithEmptyWord;
    outWithEmptyWord << trie;
    EXPECT_EQ(outWithEmptyWord.str(), "\n");
}


TEST(TrieTest, Utf8WordsCanBeStoredAndRemoved) {
    Trie trie;
    trie.insert("кот");
    trie.insert("кошка");
    trie.insert("дом");

    EXPECT_TRUE(trie.contains("кот"));
    EXPECT_TRUE(trie.contains("кошка"));
    EXPECT_EQ(trie.prefixCount("ко"), 2);
    EXPECT_EQ(trie.size(), 3);

    EXPECT_TRUE(trie.erase("кот"));
    EXPECT_FALSE(trie.contains("кот"));
    EXPECT_TRUE(trie.contains("кошка"));
    EXPECT_EQ(trie.prefixCount("ко"), 1);
}

TEST(TrieTest, Utf8PrefixSearch) {
    Trie trie;
    trie.insert("кот");
    trie.insert("котик");
    trie.insert("дом");

    const std::vector<std::string> expected = {"кот", "котик"};
    EXPECT_EQ(trie.wordsWithPrefix("кот"), expected);
}
