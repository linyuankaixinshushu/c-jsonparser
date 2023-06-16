set(CMAKE_CXX_STANDARD 17)
project(test LANGUAGES CXX)
add_library(jsonparserlib STATIC jsonparser.cpp)
target_include_directories(jsonparserlib PUBLIC .)