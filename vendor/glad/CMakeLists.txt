set(WAFFLE_GLAD_SOURCES
    gl.c

    include/glad/gl.h
)

#add_library(glad STATIC  ${WAFFLE_GLAD_SOURCES})

include_directories(glad
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
