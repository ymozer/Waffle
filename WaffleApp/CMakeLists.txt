#[[cmake_minimum_required(VERSION 3.15)
project(WaffleApp)

# Specify source files.
set(SOURCES
    main.cpp
)

# Define the executable target.
add_executable(WaffleApp ${SOURCES})

target_link_libraries(WaffleApp PRIVATE WaffleEngine)

target_include_directories(WaffleApp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../WaffleEngine
)
]]

project(test)

# Specify source files.
set(SOURCES
    test.cpp
)

# Define the executable target.
add_executable(test ${SOURCES})

target_link_libraries(test PRIVATE WaffleEngine)

target_include_directories(test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../WaffleEngine
        ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/imgui
        
)
