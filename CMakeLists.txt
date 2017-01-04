project(GeaSolution)
cmake_minimum_required(VERSION 2.8.12)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(GeaProgram main.cpp
	src/Heatmap.cpp src/Heatmap.h
	src/Histogram.cpp src/Histogram.h
	src/Trajectory.cpp src/Trajectory.h)


target_link_libraries(GeaProgram ${CONAN_LIBS})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${"GeaProgram})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "GeaProgram")
