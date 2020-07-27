cmake_minimum_required(VERSION 3.10)
project(testSBR)

set(CMAKE_CXX_STANDARD 11)

file(GLOB ${PROJECT_NAME}_SRC ./*.cpp)

add_executable(test ${${PROJECT_NAME}_SRC})