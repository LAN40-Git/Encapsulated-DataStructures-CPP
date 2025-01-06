#ifndef DATASTRUCTURES_TRIE_H
#define DATASTRUCTURES_TRIE_H

#include <string>
#include "TrieNode.h"

class Trie {
public:
    Trie() { root = new TrieNode();}
    ~Trie() { delete root;}
    void insert(const std::string &word); // 插入单词
    void erase(const std::string &word);  // 删除单词
    bool search(const std::string &word); // 查找单词
    bool startsWith(const std::string &prefix); // 查找前缀
    void reconstruct(); // 重构字典树

private:
    TrieNode *root;
};


#endif //DATASTRUCTURES_TRIE_H
