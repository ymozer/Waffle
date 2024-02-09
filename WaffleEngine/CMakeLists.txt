add_subdirectory(Util)
add_subdirectory(Core)
#add_subdirectory(Input)
#add_subdirectory(Audio)
#add_subdirectory(Renderer)
#add_subdirectory(Scene)
#add_subdirectory(Thread)


# Include directories for WaffleEngine.
# Assuming vendor/glad/include contains the GLAD headers.
add_library(WaffleEngine STATIC
    WaffleEngine.cpp
    WaffleEngine.hpp
)

# Link with external dependencies from `vendor`.
# Here we link with GLFW. GLAD is header-only, so it doesn't need to be linked.
target_link_libraries(WaffleEngine PUBLIC 
    imgui 
    imgui_impl_glfw
    imgui_impl_opengl3 
    glfw
    waffle_core
)

target_include_directories(WaffleEngine PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/vendor/glm
    ${CMAKE_SOURCE_DIR}/vendor/imgui
)

