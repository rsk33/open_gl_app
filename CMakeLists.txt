cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXTENSIONS OFF)

project(open_gl_app VERSION 1.0.0 LANGUAGES C CXX)

option(COMPILE_EXECUTABLE "Compile: ${EXECUTABLE_NAME}" ON)

#set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(FetchContent)
include(FindGLEW)
find_package(OpenGL REQUIRED)

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

add_subdirectory(lib)
if(COMPILE_EXECUTABLE)
    add_subdirectory(app)
endif()
