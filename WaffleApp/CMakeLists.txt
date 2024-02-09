cmake_minimum_required(VERSION 3.15)
project(WaffleApp)

# Specify source files.
set(SOURCES
    src/main.cpp
    src/game.cpp
)

# Define the executable target.
add_executable(WaffleApp ${SOURCES})

# Link with WaffleEngine and possibly other dependencies.
target_link_libraries(WaffleApp PRIVATE WaffleEngine)
