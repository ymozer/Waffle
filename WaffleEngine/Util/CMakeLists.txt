set (WAFFLE_UTIL_SOURCES
    Timer.cpp
    Timer.hpp
)

add_library(waffle_util STATIC ${WAFFLE_UTIL_SOURCES})
target_include_directories(waffle_util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
