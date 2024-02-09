
# Add the glad library as an interface target
add_library(glad INTERFACE)

# Set the include directory for glad
target_include_directories(glad INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
