set (WAFFLE_RENDERER_SOURCES
    Renderer.cpp
    Renderer.hpp
    #Buffer.cpp
    #Buffer.hpp
    ShaderManager.cpp
    ShaderManager.hpp
    Texture.cpp
    Texture.hpp
    #VertexArray.cpp
    #VertexArray.hpp
)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)


add_library(waffle_renderer ${WAFFLE_RENDERER_SOURCES})
target_link_libraries(waffle_renderer PUBLIC glfw waffle_util)
target_include_directories(waffle_renderer PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/stb
)




