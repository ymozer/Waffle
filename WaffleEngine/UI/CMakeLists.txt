set (WAFFLE_UI_SOURCES
    UI.cpp
    UI.hpp
    Window.cpp
    Window.hpp
)

find_package(glfw3 REQUIRED)
add_library(waffle_ui ${WAFFLE_UI_SOURCES})

target_link_libraries(waffle_ui PUBLIC glfw waffle_util waffle_input)
target_include_directories(waffle_ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/glfw
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/../)