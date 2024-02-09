#[[
set (WAFFLE_AUDIO_SOURCES
    Audio.cpp
    Audio.h
    AudioManager.cpp
    AudioManager.h
    Sound.cpp
    Sound.h
)

add_library(waffle_audio ${WAFFLE_AUDIO_SOURCES})
target_link_libraries(waffle_audio waffle_core)
target_include_directories(waffle_audio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
]]
