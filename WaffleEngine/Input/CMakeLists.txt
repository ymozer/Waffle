set (WAFFLE_INPUT_SOURCES
    Input.cpp
    Input.hpp
    KeyCodes.hpp
    MouseButtonCodes.hpp
)

find_package(glfw3 REQUIRED)
add_library(waffle_input ${WAFFLE_INPUT_SOURCES})

target_link_libraries(waffle_input PUBLIC glfw waffle_util)
target_include_directories(waffle_input PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/glfw
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/glm
    
    ${CMAKE_CURRENT_SOURCE_DIR}/../)


