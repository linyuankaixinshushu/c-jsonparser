cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
project(test LANGUAGES CXX)

add_executable(main main.cpp)

add_subdirectory(jsonparser)

target_link_libraries(main PUBLIC jsonparserlib)