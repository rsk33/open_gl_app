#include <iostream>
#include <array>
#include <algorithm>
#include <memory>
#include <cstring>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mesh.h"
#include "shader.h"
#include "window.h"
#include "camera.h"


const GLint WIDTH = 800, HEIGHT = 600;
Window mainWindow {WIDTH, HEIGHT};
Camera camera {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
    -90.0f, 0.0f, 5.0f, 0.5f};
std::vector<std::unique_ptr<Mesh>> meshList;
std::vector<std::unique_ptr<Shader>> shaderList;

const std::string vShaderFileName = "shaders/shader.vert";
const std::string fShaderFileName = "shaders/shader.frag";

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

void createObjects()
{
    std::vector<GLfloat> vertices {
		-1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

    std::vector<unsigned int> indices {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
    mesh->createMesh(vertices, indices);
    meshList.push_back(std::move(mesh));
}

void createShaders()
{
    std::unique_ptr<Shader> shader = std::make_unique<Shader>();
    shader->createFromFile(vShaderFileName, fShaderFileName);
    shaderList.emplace_back(std::move(shader));
}

int main()
{
    mainWindow.initialize();

    createObjects();
    createShaders();

    GLfloat aspectRatio = static_cast<GLfloat>(mainWindow.getBufferWidth()) /
            mainWindow.getBufferHeight();
    glm::mat4 projection = glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f);

    // Loop until window closed
    while(!mainWindow.getShouldClose())
    {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        // Get & Handle user input events
        glfwPollEvents();

        camera.keyControl(mainWindow.getKeys(), deltaTime);
        camera.mouseControl(mainWindow.getResetXChange(),
                mainWindow.getResetYChange());

        // Clear the window
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList.front()->useShader();

        GLuint uniformModel = shaderList.front()->getModelLocation();
        GLuint uniformProjection = shaderList.front()->getProjectionLocation();
        GLuint uniformView = shaderList.front()->getViewLocation();

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE,
                glm::value_ptr(camera.calculateViewMatrix()));
        meshList.front()->renderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-0.5f, -0.5f, -3.0f));
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList.front()->renderMesh();

        glUseProgram(0);
        mainWindow.swapBuffers();
    }

    return 0;
}
