cmake_minimum_required(VERSION 3.3)
project(SteppedCalcTest)

set(BOOST_ROOT "../../../boost_1_60_0")
find_package(Boost 1.60.0)
if(Boost_FOUND)
    include_directories(${BOOST_ROOT})
else()
    message(FATAL_ERROR "Could not find boost!")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
        main.cpp
        TokenizerTest.cpp
        InfixToPostfixTest.cpp
        ../TokenTypeDef.h
        ../Tokenizer.h
        ../Tokenizer.cpp
        ../InfixToPostfix.h
        ../InfixToPostfix.cpp)

add_executable(SteppedCalcTest ${SOURCE_FILES})

