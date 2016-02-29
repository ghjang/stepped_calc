cmake_minimum_required(VERSION 3.3)
project(SteppedCalcTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
        main.cpp)

add_executable(SteppedCalcTest ${SOURCE_FILES})

