#pragma once

#include <vector>
#include <GL/glew.h>

class Mesh
{
    public:
        Mesh();
        void createMesh(const std::vector<GLfloat>& vertices, const
                std::vector<unsigned int>& indices);
        void renderMesh();
        void clearMesh();
        ~Mesh();
    private:
        GLuint VAO;
        GLuint VBO;
        GLuint IBO;
        GLsizei indexCount;
};
