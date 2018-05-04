cmake_minimum_required(VERSION 3.0)
project(randomBinaryTreeGenerator)

enable_testing()
set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} randomBinaryTree.hpp example.cpp)
add_test(NAME SaberTest
        COMMAND $<TARGET_FILE:${PROJECT_NAME}>)

set(BIN_NAME "${PROJECT_NAME}InSucc")
add_executable(${BIN_NAME} randomBinaryTree.hpp inorderSuccessor.cpp)
add_test(NAME SaberTestInSucc
        COMMAND $<TARGET_FILE:${BIN_NAME}>)