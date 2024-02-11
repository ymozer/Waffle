// ShaderManager.cpp
#include "ShaderManager.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

namespace Waffle
{

    ShaderManager::ShaderManager()
    {
        start();
    }

    ShaderManager::~ShaderManager()
    {
        glDeleteProgram(ShaderProgramID);
    }

    void ShaderManager::start()
    {
        ShaderProgramID = glCreateProgram();
    }

    void ShaderManager::addShaderFromFile(const std::string &shaderPath, GLenum shaderType)
    {
        std::string shaderCode = readShaderCodeFromFile(shaderPath);
        GLuint shaderID = compileShader(shaderCode.c_str(), shaderType);
        glAttachShader(ShaderProgramID, shaderID);
        glDeleteShader(shaderID); // Delete once attached
    }

    void ShaderManager::linkProgram()
    {
        glLinkProgram(ShaderProgramID);
        checkCompileErrors(ShaderProgramID, "PROGRAM");
    }

    void ShaderManager::use()
    {
        glUseProgram(ShaderProgramID);
    }

    void ShaderManager::unuse()
    {
        glUseProgram(0);
    }

    template <typename T>
    void ShaderManager::setUniform(const std::string &name, T value)
    {
        GLint location = glGetUniformLocation(ShaderProgramID, name.c_str());
        if (location != -1)
        {
            if constexpr (std::is_same_v<T, int>)
            {
                glUniform1i(location, value);
            }
            else if constexpr (std::is_same_v<T, float>)
            {
                glUniform1f(location, value);
            }
            else if constexpr (std::is_same_v<T, glm::vec2>)
            {
                glUniform2fv(location, 1, &value[0]);
            }
            else if constexpr (std::is_same_v<T, glm::vec3>)
            {
                glUniform3fv(location, 1, &value[0]);
            }
            else if constexpr (std::is_same_v<T, glm::vec4>)
            {
                glUniform4fv(location, 1, &value[0]);
            }
            else if constexpr (std::is_same_v<T, glm::mat4>)
            {
                glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
            }
        }
        else
        {
            std::cerr << "ERROR::SHADER::UNIFORM_NOT_FOUND: " << name << std::endl;
        }
    }

    // explicit template instantiation
    template void ShaderManager::setUniform<int>(const std::string &name, int value);
    template void ShaderManager::setUniform<float>(const std::string &name, float value);
    template void ShaderManager::setUniform<glm::vec2>(const std::string &name, glm::vec2 value);
    template void ShaderManager::setUniform<glm::vec3>(const std::string &name, glm::vec3 value);
    template void ShaderManager::setUniform<glm::vec4>(const std::string &name, glm::vec4 value);
    template void ShaderManager::setUniform<glm::mat4>(const std::string &name, glm::mat4 value);



    std::string ShaderManager::readShaderCodeFromFile(const std::string &shaderPath)
    {
        std::ifstream shaderFile;
        std::stringstream shaderStream;

        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            shaderFile.open(shaderPath);
            shaderStream << shaderFile.rdbuf();
            shaderFile.close();
            return shaderStream.str();
        }
        catch (std::ifstream::failure &e)
        {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << shaderPath << std::endl;
            exit(0);
            return "";
        }
    }

    GLuint ShaderManager::compileShader(const char *shaderCode, GLenum shaderType)
    {
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);
        checkCompileErrors(shader, shaderType == GL_VERTEX_SHADER ? "VERTEX" : shaderType == GL_FRAGMENT_SHADER ? "FRAGMENT"
                                                                                                                : "OTHER");
        return shader;
    }

    void ShaderManager::checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        std::cout << shader << std::endl;
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }

} // namespace Waffle
