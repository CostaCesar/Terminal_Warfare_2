cmake_minimum_required(VERSION 3.7)
project(TerminalWarfare LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

FILE(GLOB_RECURSE source src/*.cpp)

# Sources
add_subdirectory(src)

add_executable(TerminalWarfare
${source})

target_include_directories(TerminalWarfare PRIVATE src/Classes)
target_include_directories(TerminalWarfare PRIVATE src/Interfaces)

enable_testing()
add_subdirectory(tests)