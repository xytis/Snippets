cmake_minimum_required(VERSION 2.6)

project(SDL_Project)

Find_Package ( SDL REQUIRED )
Find_Package ( SDL_image REQUIRED )
Find_Package ( SDL_ttf REQUIRED )


file(GLOB PROJECT_SRC
	"src/*.hpp"
	"src/*.cpp"
)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS_Debug "-g")

set(CMAKE_CXX_FLAGS_Release "-O2 -DNDEBUG")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE})

message(STATUS "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}:${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}}")

link_libraries(
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLTTF_LIBRARY}
)

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SRC}
)
