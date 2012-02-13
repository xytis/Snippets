cmake_minimum_required (VERSION 2.6)

project (ThreadWatcher)

ADD_LIBRARY( logger STATIC
  ../Logger/Logger.cpp
  )

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

link_libraries(pthread logger)

file(GLOB ThreadWatcher_SRC
    "*.hpp"
    "*.cpp"
)
add_executable(ThreadWatcher ${ThreadWatcher_SRC})
