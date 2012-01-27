cmake_minimum_required (VERSION 2.6)

project (LoggerTest)

enable_testing()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

link_libraries(cpptest)
file(GLOB LoggerTest_SRC
    "*.hpp"
    "*.cpp"
)
add_executable(LoggerTest ${LoggerTest_SRC})