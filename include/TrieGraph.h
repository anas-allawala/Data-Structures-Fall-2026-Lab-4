#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

struct TrieNode
{
    // pointer array for child nodes of each node
    TrieNode *children[26];

    // Used for indicating ending of string
    bool isEndOfWord;

    TrieNode()
    {
        // initialize the wordEnd variable with false
        // initialize every index of childNode array with NULL
        isEndOfWord = false;
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }
    }
};

class TrieGraph
{
public:
    TrieNode *root;

    TrieGraph()
    {
        root = new TrieNode();
    }
    void insertWord(string word);
    bool searchWord(string word);
    vector<string> startsWith(string prefix);
};

#endif