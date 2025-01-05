add_library(Trie SHARED
    src/Trie.cpp
)

add_executable(TrieTest
    tests/trie_test.cpp
)

target_include_directories(Trie PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(TrieTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(TrieTest Trie)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set_target_properties(Trie PROPERTIES OUTPUT_NAME "Trie")