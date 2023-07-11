cmake_minimum_required(VERSION 3.0)
project(udp_socket VERSION 0.0.1 LANGUAGES CXX)

include_directories(include)
add_executable(example
    src/example.cpp
    src/udp_socket.cpp)
target_compile_options(example PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
         -Wall>
    $<$<CXX_COMPILER_ID:MSVC>:
         /W4>)
