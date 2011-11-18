cmake_minimum_required (VERSION 2.6)

project (LoggerTest)

# The version number.
set (LoggerTest_VERSION_MAJOR 1)
set (LoggerTest_VERSION_MINOR 0)

file(GLOB LoggerTest_SRC
    "*.hpp"
    "*.cpp"
)
add_executable(LoggerTest ${LoggerTest_SRC})