set(LIB_SOURCES
    mesh.cpp
    shader.cpp
    window.cpp
    camera.cpp
)

set(LIB_HEADERS
    mesh.h
    shader.h
    window.h
    camera.h
)

set(LIB_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR} 
)

add_library(${LIB_NAME} STATIC ${LIB_SOURCES} ${LIB_HEADERS})

target_include_directories(${LIB_NAME} PUBLIC
    ${LIB_INCLUDES}
    glfw
    GLEW::glew
)

