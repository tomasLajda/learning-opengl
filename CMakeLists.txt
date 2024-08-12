cmake_minimum_required(VERSION 3.13)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

project(main)
set(CMAKE_CXX_STANDARD 17)

# Subdirectories
add_subdirectory(thirdparty/glad)

# Define MY_SOURCES to be a list of all the source files for the project
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c")

# Add the executable target
add_executable(main ${MY_SOURCES})

target_compile_definitions(main PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/") 
# For release builds, you might use the following:
# target_compile_definitions(main PUBLIC RESOURCES_PATH="./resources/")

# Add the include directories
target_include_directories(main PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

# Use pkg-config to find GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW3 REQUIRED glfw3)

find_package(OpenGL REQUIRED)

# Link thirdparty libraries
target_link_libraries(main PRIVATE glad ${GLFW3_LIBRARIES} OpenGL::GL)
