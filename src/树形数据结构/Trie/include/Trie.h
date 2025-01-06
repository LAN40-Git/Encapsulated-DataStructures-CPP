#ifndef DATASTRUCTURES_TRIE_H
#define DATASTRUCTURES_TRIE_H

#include <string>
#include "TrieNode.h"

class Trie {
public:
    Trie() { root = new TrieNode();}
    ~Trie() { delete root;}
    void insert(const std::string &word);
    void erase(const std::string &word);
    bool search(const std::string &word);
    bool startsWith(const std::string &prefix); // 查找前缀
    void reconstruct();

private:
    TrieNode *root;
};


#endif //DATASTRUCTURES_TRIE_H
