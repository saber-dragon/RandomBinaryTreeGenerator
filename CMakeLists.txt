cmake_minimum_required(VERSION 3.0)
project(randomBinaryTreeGenerator)

enable_testing()
set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} randomBinaryTree.hpp example.cpp)
add_test(NAME SaberTest
        COMMAND $<TARGET_FILE:${PROJECT_NAME}>)