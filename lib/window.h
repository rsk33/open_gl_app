#pragma once

#include <memory>
#include <array>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
    public:
        Window(GLint windowWidth = 800, GLint windowHeight = 600);

        int initialize();

        GLint getBufferWidth() const { return bufferWidth; }
        GLint getBufferHeight() const { return bufferHeight; }
        bool getShouldClose() const; 
        void swapBuffers() const { glfwSwapBuffers(mainWindow); }

        std::array<bool,1024>& getKeys();
        GLfloat getResetXChange();
        GLfloat getResetYChange();

        ~Window();
    private:
        GLFWwindow* mainWindow;
        GLint width;
        GLint height;
        GLint bufferWidth;
        GLint bufferHeight;

        std::array<bool,1024> keys;
        GLfloat lastX;
        GLfloat lastY;
        GLfloat xChange;
        GLfloat yChange;
        bool mouseFirstMoved;

        void createCallbacks();
        static void handleKeys(GLFWwindow* window, int key, int code, int
                action, int mode);
        static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};
