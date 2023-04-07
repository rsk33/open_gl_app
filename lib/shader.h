#pragma once

#include <string>
#include <GL/glew.h>

class Shader
{
    public:
        Shader();

        void createFromString(const std::string& vCode, const std::string& fCode);
        void createFromFile(const std::string& vShaderFileName, const
                std::string& fShaderFileName);

        GLuint getProjectionLocation() const;
        GLuint getModelLocation() const;

        void useShader() const;
        void clearShader();

        ~Shader();
    private:
        GLuint shaderID;
        GLuint uniformModel;
        GLuint uniformProjection;

        std::string readFile(const std::string& fileName) const;
        void compileShader(const std::string& vCode, const std::string& fCode);
        void addShader(const std::string& shaderCode, GLenum shaderType) const;
};
