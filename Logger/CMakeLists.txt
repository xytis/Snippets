cmake_minimum_required (VERSION 2.6)

project (LoggerTest)

ADD_LIBRARY( logger STATIC
  Logger.cpp
  )


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

link_libraries(logger)
file(GLOB LoggerTest_SRC
    "showcase.cpp"
)
add_executable(LoggerTest ${LoggerTest_SRC})
