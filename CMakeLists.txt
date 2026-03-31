cmake_minimum_required(VERSION 3.16)
project(rt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# To make the LSP work, also needed to:
# rm -rf build
# cmake -B build
# ln -s build/compile_commands.json .
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/core/*.cpp
)

# Libs that need to compile
set(LIB_SOURCES
    ${CMAKE_SOURCE_DIR}/lib/lodepng/lodepng.cpp
    ${CMAKE_SOURCE_DIR}/lib/lodepng/lodepng_util.cpp
    ${CMAKE_SOURCE_DIR}/lib/tinyxml2/tinyxml2.cpp
)

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
    ${LIB_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/lib
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wpedantic
)
