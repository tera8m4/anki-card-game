cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(BuildAll LANGUAGES CXX)

include(cmake/tools.cmake)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/cards ${CMAKE_BINARY_DIR}/cards)