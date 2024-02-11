set (WAFFLE_CORE_SOURCES
    App.cpp
    App.hpp
    Entry.hpp
    Log.cpp
    Log.hpp
)

find_package(glfw3 REQUIRED)
add_library(waffle_core ${WAFFLE_CORE_SOURCES})

target_link_libraries(waffle_core PUBLIC glfw waffle_util)
target_include_directories(waffle_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/glfw
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/stb
    ${CMAKE_CURRENT_SOURCE_DIR}/../)