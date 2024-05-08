cmake_minimum_required(VERSION 3.7)
project(TerminalWarfare LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

FILE(GLOB_RECURSE source src/*.cpp)

# Sources
add_executable(TerminalWarfare
${source})