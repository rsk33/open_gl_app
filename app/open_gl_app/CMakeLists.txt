set(EXECUTABLE_SOURCE
    main.cpp
)

add_executable(${EXECUTABLE_NAME} ${EXECUTABLE_SOURCE})

target_link_libraries(${EXECUTABLE_NAME} PUBLIC 
    ${LIB_NAME}
    glfw
    ${glew_LIBRARIES}
    GLEW::glew
    ${OPENGL_LIBRARIES}
)
