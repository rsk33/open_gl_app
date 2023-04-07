#include "window.h"

#include <iostream>


Window::Window(GLint windowWidth, GLint windowHeight)
    : width{windowWidth}
    , height{windowHeight}
    , bufferWidth{0}
    , bufferHeight{0}
    , lastX{0}
    , lastY{0}
    , xChange{0}
    , yChange{0}
    , mouseFirstMoved{false}
{
    keys.fill(false);
}

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

    // Handle Key + Mouse input
    createCallbacks();
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    glfwSetWindowUserPointer(mainWindow, this);
 
    return 0;
}
    
bool Window::getShouldClose() const
{
    return glfwWindowShouldClose(mainWindow);
}

std::array<bool,1024>& Window::getKeys()
{
    return keys;
}

GLfloat Window::getResetXChange()
{
    const auto res = xChange;
    xChange = 0;
    return res;
}

GLfloat Window::getResetYChange()
{
    const auto res = yChange;
    yChange = 0;
    return res;
}

Window::~Window()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}

void Window::createCallbacks()
{
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action,
        int mode)
{
    Window* theWindow =
        static_cast<Window*>(glfwGetWindowUserPointer(window));

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if(key >= 0 && key < theWindow->keys.size())
    {
        if(action == GLFW_PRESS)
        {
            theWindow->keys[key] = true;
        }
        else if(action == GLFW_RELEASE)
        {
            theWindow->keys[key] = false;
        }
    }
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
    Window* theWindow =
        static_cast<Window*>(glfwGetWindowUserPointer(window));

    if(!theWindow->mouseFirstMoved)
    {
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMoved = true;
    }

    theWindow->xChange = xPos - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - yPos;

    theWindow->lastX = xPos;
    theWindow->lastY = yPos;
}
