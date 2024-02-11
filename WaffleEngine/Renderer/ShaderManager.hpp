#pragma once

#include <glad/gl.h>
#include <string>

namespace Waffle
{
    class ShaderManager
    {
    public:
        ShaderManager();
        ~ShaderManager();
        void start();
        void addShaderFromFile(const std::string &shaderPath, GLenum shaderType);
        void linkProgram();
        void use();
        void unuse();

        template <typename T>
        void setUniform(const std::string &name, T value);

    private:
        GLuint ShaderProgramID;
        std::string readShaderCodeFromFile(const std::string &shaderPath);
        GLuint compileShader(const char *shaderCode, GLenum shaderType);
        void checkCompileErrors(GLuint shader, std::string type);
    };
}