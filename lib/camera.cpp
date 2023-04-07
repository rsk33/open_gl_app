#include "camera.h"
#include <algorithm>


Camera::Camera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch,
        GLfloat moveSpeed, GLfloat turnSpeed)
    : m_position{position}
    , m_front{glm::vec3(0.0f, 0.0f, -1.0f)}
    , m_up{0}
    , m_right{0}
    , m_worldUp{worldUp}
    , m_yaw{yaw} 
    , m_pitch{pitch} 
    , m_roll{0} 
    , m_moveSpeed{moveSpeed} 
    , m_turnSpeed{turnSpeed}
{
    update();
}

void Camera::keyControl(std::array<bool,1024>& keys, GLfloat dTime)
{
    GLfloat velocity = m_moveSpeed * dTime;
    if(keys[GLFW_KEY_W])
    {
        m_position += m_front * velocity;
    } 

    if(keys[GLFW_KEY_S])
    {
        m_position -= m_front * velocity;
    } 
    
    if(keys[GLFW_KEY_A])
    {
        m_position -= m_right * velocity;
    } 

    if(keys[GLFW_KEY_D])
    {
        m_position += m_right * velocity;
    } 
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
    xChange *= m_turnSpeed;
    yChange *= m_turnSpeed;
    
    m_yaw += xChange;
    m_pitch += yChange;

    m_pitch = std::max(std::min(m_pitch, 89.9f), -89.9f);

    update();
}

glm::mat4 Camera::calculateViewMatrix()
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::update()
{
    m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front.y = sin(glm::radians(m_pitch));
    m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(m_front);

    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}
