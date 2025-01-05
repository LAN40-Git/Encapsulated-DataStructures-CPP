#ifndef DATASTRUCTURES_TRIENODE_H
#define DATASTRUCTURES_TRIENODE_H
#include <unordered_map>

class TrieNode {
public:
    bool isEnd;
    std::unordered_map<char,TrieNode*> children;
    TrieNode() : isEnd(false) {}
    ~TrieNode() {
        for (auto& node : children) {
            delete node.second;
        }
    }
};

#endif //DATASTRUCTURES_TRIENODE_H
