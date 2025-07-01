cmake_minimum_required(VERSION 3.10.0)
project(HextTer CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffast-math")


file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/*.cpp)

add_executable(hexter ${SOURCES})

install(TARGETS hexter DESTINATION bin)

