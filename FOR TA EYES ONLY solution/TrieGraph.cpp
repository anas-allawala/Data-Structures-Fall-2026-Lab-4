#include "../include/TrieGraph.h"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void TrieGraph::insertWord(string word)
{
    TrieNode *curr = root;
    for (char c : word)
    {
        // Safety check to ignore invalid characters
        if (c < 'a' || c > 'z')
            continue;
        int index = c - 'a';

        // BUG FIX: Only create a new node if one does not already exist
        if (curr->children[index] == nullptr)
        {
            curr->children[index] = new TrieNode();
        }
        curr = curr->children[index];
    }
    // BUG FIX: curr is now pointing to the final node, just flag it
    curr->isEndOfWord = true;
}

bool TrieGraph::searchWord(string word)
{
    TrieNode *curr = root;
    for (char c : word)
    {
        if (c < 'a' || c > 'z')
            continue;
        int index = c - 'a';
        if (curr->children[index] == nullptr)
        {
            return false;
        }
        curr = curr->children[index];
    }
    return curr->isEndOfWord;
}

// ---------------------------------------------------------
// Recursive Helper for Prefix Search
// ---------------------------------------------------------
void startsWithHelper(TrieNode *curr, string currentPrefix, vector<string> &results)
{
    if (curr == nullptr)
        return;

    if (curr->isEndOfWord)
    {
        results.push_back(currentPrefix);
    }

    for (int i = 0; i < 26; i++)
    {
        if (curr->children[i] != nullptr)
        {
            startsWithHelper(curr->children[i], currentPrefix + (char)('a' + i), results);
        }
    }
}

vector<string> TrieGraph::startsWith(string prefix)
{
    vector<string> results;
    TrieNode *curr = root;

    // Traverse down to the end of the requested prefix
    for (char c : prefix)
    {
        if (c < 'a' || c > 'z')
            return results;
        int index = c - 'a';
        if (curr->children[index] == nullptr)
        {
            return results; // Prefix does not exist in the Trie
        }
        curr = curr->children[index];
    }

    // Recursively collect all words branching from this point
    startsWithHelper(curr, prefix, results);
    return results;
}

// ---------------------------------------------------------
// Substring Suffix Trie Generator
// ---------------------------------------------------------

// Local struct to build a Suffix Trie that handles spaces and stores original indices
struct SuffixNode
{
    unordered_map<char, SuffixNode *> children;
    int startIndex = -1;

    // Destructor to automatically clean up memory
    ~SuffixNode()
    {
        for (auto &pair : children)
        {
            delete pair.second;
        }
    }
};

int TrieGraph::substring(string text, string pattern)
{
    SuffixNode suffixRoot;

    // 1. Generate the Suffix Trie from the text
    for (int i = 0; i < text.length(); i++)
    {
        SuffixNode *curr = &suffixRoot;
        for (int j = i; j < text.length(); j++)
        {
            char c = text[j];
            if (curr->children.find(c) == curr->children.end())
            {
                curr->children[c] = new SuffixNode();
            }
            curr = curr->children[c];

            // Store the starting index of this specific suffix
            if (curr->startIndex == -1)
            {
                curr->startIndex = i;
            }
        }
    }

    // 2. Search the generated Suffix Trie for the pattern
    SuffixNode *curr = &suffixRoot;
    for (char c : pattern)
    {
        if (curr->children.find(c) == curr->children.end())
        {
            return -1; // Pattern not found
        }
        curr = curr->children[c];
    }

    return curr->startIndex;
}