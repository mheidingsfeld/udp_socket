# Build example: Simple
add_executable(simple)
target_sources(simple
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/simple.cpp
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
        ${CMAKE_CURRENT_LIST_DIR}/loopback.cpp
    )
target_include_directories(loopback
    PRIVATE
        ${PROJECT_SOURCE_DIR}
    )    
target_link_libraries(loopback 
    PRIVATE 
        ${PROJECT_NAME}
    )   