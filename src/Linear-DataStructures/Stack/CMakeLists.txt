add_executable(StackTest
        tests/StackTest.cpp
)

target_include_directories(StackTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)