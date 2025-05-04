cmake_minimum_required(VERSION 3.10)

project(Compiler LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)
set(MAIN_FILE ${CMAKE_SOURCE_DIR}/main.cpp)
set(SOURCES ${MAIN_FILE} ${SOURCES})
message(${SOURCES})
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(compiler ${SOURCES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


