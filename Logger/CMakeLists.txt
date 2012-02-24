cmake_minimum_required (VERSION 2.6)

project (LoggerShowcase)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

link_libraries(pthread)

file(GLOB LoggerShowcase_SRC
    "showcase.cpp"
)
add_executable(LoggerShowcase ${LoggerShowcase_SRC})
