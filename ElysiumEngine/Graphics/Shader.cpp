// Shader.cpp
#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../vendor/glm/gtc/type_ptr.hpp"

#include "../Core/Log.h"


using namespace Graphics;


Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
{

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    CompileShader(vertexSource, vertexShader);
    CompileShader(fragmentSource, fragmentShader);


    m_programID = glCreateProgram();
    glAttachShader(m_programID, vertexShader);
    glAttachShader(m_programID, fragmentShader);
    glLinkProgram(m_programID);

    GLint success = 0;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<char> errorLog(maxLength);
        glGetProgramInfoLog(m_programID, maxLength, &maxLength, &(errorLog[0]));

        Core::Log::Instance().Out(Core::LogLevel::Error) << "OpenGL Error : Program failed to link : \n \n" << errorLog.data();

        // We don't need the program anymore.
        glDeleteProgram(m_programID);
        // Don't leak shaders either.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Use the infoLog as you see fit.

        // In this simple program, we'll just leave
        return;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_programID);
}

void Shader::Use() const
{
    glUseProgram(m_programID);
}

GLuint Shader::GetUniformLocation(const std::string& name) const
{
    return glGetUniformLocation(m_programID, name.c_str());
}

void Shader::SetUniform(const std::string& name, float value) const
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform(const std::string& name, const glm::mat4& matrix) const
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetUniform(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

bool Graphics::Shader::CompileShader(const std::string& source, GLuint id) const
{

    const char* shaderSource = source.c_str();

    glShaderSource(id, 1, &shaderSource, nullptr);

    glCompileShader(id);

    GLint vertexSuccess = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &vertexSuccess);
    if (vertexSuccess == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> errorLog(maxLength);
        GLint actualLength = 0;  // New variable to store the actual length

        glGetShaderInfoLog(id, maxLength, &actualLength, errorLog.data());  // Pass actualLength as the last parameter

        glDeleteShader(id);

        Core::Log::Instance().Out(Core::LogLevel::Error) << "OpenGL Error : Shader failed to compile : \n \n" << errorLog.data();

    }

    return vertexSuccess == GL_TRUE;

}
