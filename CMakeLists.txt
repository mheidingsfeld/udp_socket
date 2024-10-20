cmake_minimum_required(VERSION 3.5)
project(udp_socket LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
if (MSVC)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()

# Dependencies

# Build instructions
add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}/udp_socket.cpp
    )
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}
    )
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    )

# Build example: Simple
add_executable(simple)
target_sources(simple
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/examples/simple.cpp
    )
target_include_directories(simple
    PRIVATE
        ${PROJECT_SOURCE_DIR}
    )    
target_link_libraries(simple 
    PRIVATE 
        ${PROJECT_NAME}
    )

# Build example: Loopback
add_executable(loopback)
target_sources(loopback
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/examples/loopback.cpp
    )
target_include_directories(loopback
    PRIVATE
        ${PROJECT_SOURCE_DIR}
    )    
target_link_libraries(loopback 
    PRIVATE 
        ${PROJECT_NAME}
    )   

