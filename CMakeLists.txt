cmake_minimum_required(VERSION 3.28.2)
project(WaffleProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CURR_TARGET "WaffleProject")

option(WAFFLE_INSTALL "Install WaffleEngine and WaffleApp" ON)

message( STATUS "Architecture: ${ARCHITECTURE}" )
message( STATUS "CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}" )
message( STATUS "CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}" )
message( STATUS "CMAKE_SYSTEM: ${CMAKE_SYSTEM}" )
message( STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}" )
message( STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}" )
message( STATUS "CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION}" )


if (CMAKE_COMPILER_IS_GNUCXX OR (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang"))
    set(WAFFLE_CXX_FLAGS -Wshadow -Wall -Wextra -Wno-comment -Wno-missing-field-initializers -Wno-empty-body)
    if (${CMAKE_CXX_COMPILER_ID} MATCHES "(Clang)|(AppleClang)")
        set(WAFFLE_CXX_FLAGS ${WAFFLE_CXX_FLAGS} -Wno-backslash-newline-escape)
    endif()
    if (NOT (${CMAKE_BUILD_TYPE} MATCHES "Release"))
        message("Enabling frame pointer for profiling/debug.")
        set(WAFFLE_CXX_FLAGS ${WAFFLE_CXX_FLAGS} -fno-omit-frame-pointer)
    endif()
    if (CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
        message("Enabling SSE3 support.")
        set(WAFFLE_CXX_FLAGS ${WAFFLE_CXX_FLAGS} -msse3)
    endif()
elseif (MSVC)
    set(WAFFLE_CXX_FLAGS /D_CRT_SECURE_NO_WARNINGS /wd4267 /wd4244 /wd4309 /wd4005 /MP)
endif()

# Set definitions
add_compile_definitions($<$<CONFIG:Debug>:DEBUG_MODE>)
add_compile_definitions($<$<CONFIG:Release>:RELEASE_MODE>)
add_compile_definitions($<$<CONFIG:RelWithDebInfo>:RELWITHDEBINFO_MODE>)
add_compile_definitions($<$<CONFIG:MinSizeRel>:MINSIZEREL_MODE>)


# Optionally, set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Add the vendor directory
add_subdirectory(vendor)

# Add WaffleEngine and WaffleApp subdirectories
add_subdirectory(WaffleEngine)
add_subdirectory(WaffleApp)

