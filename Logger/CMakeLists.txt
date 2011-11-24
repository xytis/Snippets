cmake_minimum_required (VERSION 2.6)

project (LoggerTest)

enable_testing()

link_libraries(cpptest)
file(GLOB LoggerTest_SRC
    "*.hpp"
    "*.cpp"
)
add_executable(LoggerTest ${LoggerTest_SRC})