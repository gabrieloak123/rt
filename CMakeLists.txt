cmake_minimum_required(VERSION 3.16)
project(rt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# Include directories
# -----------------------------
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/lib/CLI11
    ${CMAKE_SOURCE_DIR}/lib/cyCodeBase
    ${CMAKE_SOURCE_DIR}/lib/lodepng
    ${CMAKE_SOURCE_DIR}/lib/tinyxml2
)

# -----------------------------
# Source files
# -----------------------------
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/core/*.cpp
)

# libs que precisam compilar
set(LIB_SOURCES
    ${CMAKE_SOURCE_DIR}/lib/lodepng/lodepng.cpp
    ${CMAKE_SOURCE_DIR}/lib/lodepng/lodepng_util.cpp
    ${CMAKE_SOURCE_DIR}/lib/tinyxml2/tinyxml2.cpp
)

# -----------------------------
# Executable
# -----------------------------
add_executable(${PROJECT_NAME}
    ${SRC_FILES}
    ${LIB_SOURCES}
)

# -----------------------------
# (Opcional) warnings legais
# -----------------------------
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wpedantic
)

# -----------------------------
# Include directories
# -----------------------------
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/CLI11
)
target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/lib/cyCodeBase
)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/lodepng
)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/tinyxml2
)
