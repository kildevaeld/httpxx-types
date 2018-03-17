cmake_minimum_required(VERSION 3.10)
project(httpx_types)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(http_parser)

#include_directories(${PROJECT_SOURCE_DIR}/include)
#include_directories(${PROJECT_SOURCE_DIR}/vendor/http-parser)
#add_library(http_parser ${PROJECT_SOURCE_DIR}/vendor/http-parser/http_parser.c)

add_subdirectory(src)