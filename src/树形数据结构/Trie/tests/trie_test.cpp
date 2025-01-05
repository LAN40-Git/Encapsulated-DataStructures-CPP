#include "Trie.h"
#include <iostream>

int main() {
    Trie trie;
    trie.insert("app");
    trie.insert("apple");
    if (trie.search("app"))
        std::cout << "Find word：app!" << std::endl;
    if (trie.search("apple"))
        std::cout << "Find word：apple!" << std::endl;
    trie.erase("app");
    if (!trie.search("app"))
        std::cout << "Delete word：app!" << std::endl;
    if (trie.search("apple"))
        std::cout << "Find word：apple!" << std::endl;
    return 0;
}
