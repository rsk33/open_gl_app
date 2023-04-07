cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXTENSIONS OFF)

set(PROJECT_NAME "open_gl_app" CACHE STRING "Select Project")
set_property(
    CACHE PROJECT_NAME
    PROPERTY STRINGS
    "open_gl_app"
    "1_triangle"
)

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES C CXX)

#set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(FetchContent)
include(FindGLEW)
find_package(OpenGL REQUIRED)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8 
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glfw)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(LIB_NAME lib)
set(EXECUTABLE_NAME ${PROJECT_NAME})

option(COMPILE_EXECUTABLE "Compile: ${EXECUTABLE_NAME}" ON)

add_subdirectory(lib)
add_subdirectory(app)
