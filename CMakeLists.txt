project(GeaSolution)
cmake_minimum_required(VERSION 2.8.12)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(GeaProgram main.cpp, histogram.cpp)
include_directories([Before] includes.h, histogram.h)
target_link_libraries(GeaProgram ${CONAN_LIBS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "GeaProgram")
