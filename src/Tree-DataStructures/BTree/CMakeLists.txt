add_executable(BTreeTest
        tests/BTreeTest.cpp
)

target_include_directories(BTreeTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)