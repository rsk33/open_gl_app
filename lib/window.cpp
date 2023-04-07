#include "window.h"

#include <iostream>


Window::Window() : width{800}, height{600}, bufferWidth{0}, bufferHeight{0} {}

Window::Window(GLint windowWidth, GLint windowHeight) :
    width{windowWidth}, height{windowHeight}, bufferWidth{0}, bufferHeight{0} {}

int Window::initialize()
{
    if(!glfwInit())
    {
        std::cout << "GLFW initialization failed!\n";
        glfwTerminate();
        return 1;
    }
    
    // Setup GLFW Windows Properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compaibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    mainWindow = glfwCreateWindow(width, height, "TestWindow", nullptr, nullptr);

    if(!mainWindow)
    {
        std::cout << "GLFW window creation failed!\n";
        glfwTerminate();
        return 1;
    }

    // Get Buffer size information
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        std::cout << "GLEW initializaion failed!\n";
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    // Setup Viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    return 0;
}
    
bool Window::getShouldClose() const
{
    return glfwWindowShouldClose(mainWindow);
}

Window::~Window()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}
