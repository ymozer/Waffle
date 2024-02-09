
# Specify source files.
set(SOURCES
    src/Waffle.cpp
)

# Define the library target.
add_library(WaffleEngine ${SOURCES})

# Include directories for WaffleEngine.
# Assuming vendor/glad/include contains the GLAD headers.
target_include_directories(WaffleEngine PUBLIC
    include
    ${CMAKE_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/vendor/glm
    ${CMAKE_SOURCE_DIR}/vendor/imgui
)

# Link with external dependencies from `vendor`.
# Here we link with GLFW. GLAD is header-only, so it doesn't need to be linked.
target_link_libraries(WaffleEngine PUBLIC 
    imgui 
    imgui_impl_glfw
    imgui_impl_opengl3 
    glfw
)
