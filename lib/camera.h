#pragma once

#include <array>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
    public:
        Camera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat
                pitch, GLfloat moveSpeed, GLfloat turnSpeed);

        void keyControl(std::array<bool,1024>& keys, GLfloat dTime);
        void mouseControl(GLfloat xChange, GLfloat yChange);

        glm::mat4 calculateViewMatrix();

        ~Camera(){};

    private:
        glm::vec3 m_position;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_worldUp;

        GLfloat m_yaw;
        GLfloat m_pitch;
        GLfloat m_roll;

        GLfloat m_moveSpeed;
        GLfloat m_turnSpeed;

        void update();
};
