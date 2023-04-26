set(LIB_SOURCES
    mesh.cpp
    texture.cpp
    shader.cpp
    window.cpp
    camera.cpp
)

set(LIB_HEADERS
    mesh.h
    texture.h
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
    "${CMAKE_SOURCE_DIR}/external"
    glfw
    GLEW::glew
)

