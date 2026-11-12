#include "../include/TrieGraph.h"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void TrieGraph::insertWord(string word)
{
    // -Use a current pointer to keep track of which node you are currently on beginning with root.
    // -Loop through each character in the word.
    // -Hint: Subtract 'a' from the current character to find the approriate index to go to inside
    //  the children array of the current pointer.
    // -If empty, allocate a new TrieNode for that position in the children array.
    // -Re-assign current pointer to be the current node you are on in children array.
    // -Move onto the next character in the word and repeat
    // -If end of word is reached, assign current pointer's isEndOfWord bool as true.
    return;
}


bool TrieGraph::searchWord(string word)
{
    // -Use a current pointer to keep track of which node you are currently on beginning with root.
    // -Loop through each character in the word.
    // -Hint: Subtract 'a' from the current character to find the approriate index to go to inside
    //  the children array of the current pointer.
    // -If empty position in children array is reached then word was not found and you may return false.
    // -Re-assign current pointer to be the current node you are on in children array.
    // -Move onto the next character in the word and repeat
    // -If end of word is reached AND isEndOfWord bool for current pointer is true, then word is found 
    //  and you may return true.
    return false;
}


// ---------------------------------------------------------
// Recursive Helper for Prefix Search
// (you may change the function signature of the helper, or not use it at all, your choice)
// ---------------------------------------------------------
void startsWithHelper(TrieNode *curr, string currentPrefix, vector<string> &results)
{
    // 1. Base Case / Safety Check: 
    //    If 'curr' is nullptr, just return (stop exploring this path).

    // 2. Check if we found a word:
    //    If the 'curr' node's isEndOfWord is true:
        // We found a complete word! Add 'currentWord' to the results vector.

    // 3. Explore all possible next letters (children):
    //    Loop from i = 0 up to 25:
        // a. If the child pointer at index 'i' is NOT nullptr (meaning a letter exists here):
            // i. Calculate what actual character this index represents 
            //    (Hint: char nextLetter = 'a' + i)
            
            // ii. Recursively call startsWithHelper. Pass in:
            //     - The child node pointer
            //     - The 'currentWord' + the new 'nextLetter'
            //     - The results vector
}

vector<string> TrieGraph::startsWith(string prefix)
{
    // 1. Create an empty vector of strings to hold the results.

    // 2. Create a pointer (let's call it 'curr') and set it to the root of the Trie.

    // 3. Loop through every character 'c' in the given prefix:
        // a. Convert the character to an index (0 to 25). Hint: int index = c - 'a';
        // b. If the child pointer at this index is nullptr:
            // The prefix doesn't exist in our Trie! Return the empty results vector.
        // c. Otherwise, move 'curr' down to this child node.

    // 4. If the loop finishes successfully, 'curr' is now pointing to the node 
    //    that represents the last letter of the prefix.
    
    // 5. Call your recursive helper function. Pass in:
    //    - The 'curr' node pointer
    //    - The original 'prefix' string (as the starting word to build upon)
    //    - The results vector (make sure it is passed by reference in the helper!)

    // 6. Return the results vector.

    vector<string> results;
    TrieNode *curr = root;
    startsWithHelper(curr, prefix, results);
    return results;
}