# GLAD
add_subdirectory(glad)

# GLM
include_directories(glm)

# STB
include_directories(stb)

# GLFW
add_subdirectory(glfw)

# ImGui Library
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
add_subdirectory(imgui)