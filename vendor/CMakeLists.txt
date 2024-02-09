# GLFW
add_subdirectory(glfw)

# GLAD
include_directories(glad/include)

# GLM
include_directories(glm)


# ImGui Library
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
add_subdirectory(imgui)