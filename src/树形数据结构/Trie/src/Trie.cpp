#include "Trie.h"

void Trie::insert(const std::string &word) {
    TrieNode *node = root;
    for (char ch : word) {
        auto it = node->children.find(ch);
        if (it != node->children.end())
            node = it->second;
        else {
            auto trieNode = new TrieNode();
            node->children.insert({ch,trieNode});
            node = trieNode;
        }
    }
    node->isEnd = true;
}

void Trie::erase(const std::string &word) {
    TrieNode *node = root;
    TrieNode *eraseNode = nullptr; // 需要被删除的节点
    for (int i = 0; i < word.length(); i++) {
        auto it = node->children.find(word[i]);
        // 单词不存在，直接返回
        if (it == node->children.end())
            return;
        else {
            node = it->second;
            if (i == word.length()-1) { // 遍历到单词末尾
                // 如果单词末对应的节点含有子节点，说明不可删除(会影响其它单词或前缀)
                if (!node->children.empty()) {
                    eraseNode = nullptr; // 不删除任何节点
                    node->isEnd = false; // 更改标记即可
                    return;
                }
            }
            it = node->children.find(word[i+1]);
            // 如果节点有且仅有需要被删除的子节点，说明这个节点可能需要被删除
            if (it != node->children.end() && node->children.size() == 1) {
                // 删除最先被标记的可删除的节点
                if (eraseNode == nullptr)
                    eraseNode = node;
            }
            // 否则说明不包含该单词，直接返回
            else
                return;
        }
    }
    // 如果有需要被删除的节点，则删除
    if (eraseNode != nullptr) {
        delete eraseNode;
        eraseNode = nullptr;
    }
    return;
}

bool Trie::search(const std::string &word) {
    TrieNode *node = root;
    for (char ch : word) {
        auto it = node->children.find(ch);
        if (it != node->children.end())
            node = it->second;
        else
            return false;
    }
    if (node->isEnd)
        return true;
    else
        return false;
}

bool Trie::startsWith(const std::string &prefix) {
    TrieNode *node = root;
    for (char ch : prefix) {
        auto it = node->children.find(ch);
        if (it != node->children.end())
            node = it->second;
        else
            return false;
    }
    return true;
}

void Trie::reconstruct() {
    delete root;
    root = new TrieNode();
}


