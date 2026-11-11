#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "TrieGraph.h"
#include <vector>
#include <string>
#include <algorithm>

// ---------------------------------------------------------
// TASK 3: TRIE DATA STRUCTURE TESTS (50 MARKS)
// ---------------------------------------------------------

TEST_CASE("t3_insert_word" * doctest::test_suite("task3")) {
    TrieGraph t;
    t.insertWord("cat");
    
    // Inspect internal nodes directly
    CHECK(t.root != nullptr);
    
    // Use array indexing (char - 'a') and check for nullptr
    CHECK(t.root->children['c' - 'a'] != nullptr);
    
    auto c_node = t.root->children['c' - 'a'];
    CHECK(c_node->children['a' - 'a'] != nullptr);
    
    auto a_node = c_node->children['a' - 'a'];
    CHECK(a_node->children['t' - 'a'] != nullptr);
    
    auto t_node = a_node->children['t' - 'a'];
    CHECK(t_node->isEndOfWord == true);
    
    // Intermediate nodes shouldn't be end of word
    CHECK(a_node->isEndOfWord == false); 
}

TEST_CASE("t3_search_word" * doctest::test_suite("task3")) {
    TrieGraph t;
    
    // Inject manually to test only search functionality
    t.root->children['h' - 'a'] = new TrieNode();
    t.root->children['h' - 'a']->children['i' - 'a'] = new TrieNode();
    t.root->children['h' - 'a']->children['i' - 'a']->isEndOfWord = true;

    CHECK(t.searchWord("hi") == true);
    CHECK(t.searchWord("h") == false); // Exists but not end of word
    CHECK(t.searchWord("hello") == false); // Doesn't exist
}

TEST_CASE("t3_starts_with" * doctest::test_suite("task3")) {
    TrieGraph t;
    t.insertWord("car");
    t.insertWord("card");
    t.insertWord("cart");
    t.insertWord("dog");

    std::vector<std::string> results = t.startsWith("car");

    CHECK(results.size() == 3);

    // Sort to handle arbitrary order returns
    if (results.size() == 3) {
        std::sort(results.begin(), results.end());
        CHECK(results[0] == "car");
        CHECK(results[1] == "card");
        CHECK(results[2] == "cart");
    }
}