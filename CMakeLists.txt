cmake_minimum_required(VERSION 3.0)
project(udp_socket VERSION 0.0.1 LANGUAGES CXX)

# Compiler options
if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
if (MSVC)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()

# Include directories
include_directories(include)

## Build UDP Socket library
add_library(${PROJECT_NAME} src/udp_socket.cpp)

# Build example: Simple
add_executable(simple examples/simple.cpp)
target_link_libraries(simple ${PROJECT_NAME})

# Build example: Loopback
add_executable(loopback examples/loopback.cpp)
target_link_libraries(loopback ${PROJECT_NAME})
