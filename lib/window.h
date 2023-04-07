#pragma once

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
    public:
        Window();
        Window(GLint windowWidth, GLint windowHeight);

        int initialize();

        GLint getBufferWidth() const { return bufferWidth; }
        GLint getBufferHeight() const { return bufferHeight; }
        bool getShouldClose() const; 
        void swapBuffers() const { glfwSwapBuffers(mainWindow); }

        ~Window();
    private:
        GLFWwindow* mainWindow;
        GLint width;
        GLint height;
        GLint bufferWidth;
        GLint bufferHeight;
};
