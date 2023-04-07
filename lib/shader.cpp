#include "shader.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Shader::Shader() : shaderID{0}, uniformModel{0}, uniformProjection{0},
    uniformView{0} {}

void Shader::createFromString(const std::string& vCode, const std::string& fCode)
{
    compileShader(vCode, fCode);
}

void Shader::createFromFile(const std::string& vShaderFileName, const
                std::string& fShaderFileName)
{
    std::string vCode = readFile(vShaderFileName);
    std::string fCode = readFile(fShaderFileName);

    if(!vCode.empty() && !fCode.empty())
    {
        compileShader(vCode, fCode);
    }
}

GLuint Shader::getModelLocation() const
{
    return uniformModel;
}

GLuint Shader::getProjectionLocation() const
{
    return uniformProjection;
}

GLuint Shader::getViewLocation() const
{
    return uniformView;
}

void Shader::useShader() const
{
    glUseProgram(shaderID);
}

void Shader::clearShader()
{
    if(shaderID != 0)
    {
        glDeleteProgram(shaderID);
        shaderID = 0;
        uniformModel = 0;   
        uniformProjection = 0;
        uniformView = 0;
    }
}

Shader::~Shader()
{
    clearShader();
}

std::string Shader::readFile(const std::string& fileName) const
{
    std::string result;
    std::ifstream ifs (fileName);
    if(!ifs.is_open())
    {
        std::cout << "Failed to open: " << fileName << '\n';
    }
    else
    {
        std::string line;
        while(std::getline(ifs, line))
        {
            result.append(line + '\n');
        }
    }
    return result;
}

void Shader::compileShader(const std::string& vCode, const std::string& fCode)
{
    shaderID = glCreateProgram();

    if(!shaderID){
        std::cout << "Error creating shader program\n";
        return;
    }

    addShader(vCode, GL_VERTEX_SHADER);
    addShader(fCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if(!result){
        glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        std::cout << "Error linking program: " << eLog << '\n';
        return;
    }

    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if(!result){
        glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        std::cout << "Error validating program: " << eLog << '\n';
        return;
    }
    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
}

void Shader::addShader(const std::string& shaderCode, GLenum shaderType) const
{
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode.c_str();

    GLint codeLength[1];
    codeLength[0] = shaderCode.size();

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);
    
    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if(!result){
        glGetShaderInfoLog(theShader, sizeof(eLog), nullptr, eLog);
        std::cout << "Error compile shader: " << shaderType << eLog << '\n';
        return;
    }
    glAttachShader(shaderID, theShader);
}
