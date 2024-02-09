set (WAFFLE_CORE_SOURCES
    App.cpp
    App.hpp
    Entry.hpp
    Log.cpp
    Log.hpp
    Window.cpp
    Window.hpp
)

add_library(waffle_core ${WAFFLE_CORE_SOURCES})

find_package(glfw3 REQUIRED)
target_link_libraries(waffle_core PUBLIC glfw waffle_util)
target_include_directories(waffle_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/glfw
    ${CMAKE_CURRENT_SOURCE_DIR}/../)