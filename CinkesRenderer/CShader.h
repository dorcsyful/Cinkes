#ifndef SHADER_H
#define SHADER_H
#pragma once
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include "CRenderDefines.h"
namespace Cinkes
{
    class CShader
    {
    public:
        unsigned int ID;
        const char* m_VertexPath;
        const char* m_FragmentPath;
        // constructor generates the shader on the fly
        // ------------------------------------------------------------------------
        CShader(const char* a_Vertex, const char* a_Fragment)
        {
            m_VertexPath = a_Vertex;
            m_FragmentPath = a_Fragment;
            // 1. retrieve the vertex/fragment source code from filePath
            std::string vertex_code;
            std::string fragment_code;
            std::ifstream v_shader_file;
            std::ifstream f_shader_file;
            // ensure ifstream objects can throw exceptions:
            v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try
            {
                // open files
                v_shader_file.open(a_Vertex);
                f_shader_file.open(a_Fragment);
                std::stringstream vShaderStream, fShaderStream;
                // read file's buffer contents into streams
                vShaderStream << v_shader_file.rdbuf();
                fShaderStream << f_shader_file.rdbuf();
                // close file handlers
                v_shader_file.close();
                f_shader_file.close();
                // convert stream into string
                vertex_code = vShaderStream.str();
                fragment_code = fShaderStream.str();
            }
            catch (std::ifstream::failure& e)
            {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
            }
            const char* vShaderCode = vertex_code.c_str();
            const char* fShaderCode = fragment_code.c_str();
            // 2. compile shaders
            unsigned int vertex, fragment;
            // vertex shader
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vShaderCode, NULL);
            glCompileShader(vertex);
            checkCompileErrors(vertex, "VERTEX");
            // fragment Shader
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, NULL);
            glCompileShader(fragment);
            checkCompileErrors(fragment, "FRAGMENT");
            // shader Program
            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            glLinkProgram(ID);
            checkCompileErrors(ID, "PROGRAM");
            // delete the shaders as they're linked into our program now and no longer necessary
            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }
        // activate the shader
        // ------------------------------------------------------------------------
        void Use()
        {
            glUseProgram(ID);
        }
        // utility uniform functions
        // ------------------------------------------------------------------------
        void setBool(const std::string& a_Name, bool a_Value) const
        {
            glUniform1i(glGetUniformLocation(ID, a_Name.c_str()), static_cast<int>(a_Value));
        }
        // ------------------------------------------------------------------------
        void setInt(const std::string& a_Name, int a_Value) const
        {
            glUniform1i(glGetUniformLocation(ID, a_Name.c_str()), a_Value);
        }
        // ------------------------------------------------------------------------
        void setFloat(const std::string& a_Name, float a_Value) const
        {
            glUniform1f(glGetUniformLocation(ID, a_Name.c_str()), a_Value);
        }
        // ------------------------------------------------------------------------
        void setVec2(const std::string& a_Name, const glm::vec2& a_Value) const
        {
            glUniform2fv(glGetUniformLocation(ID, a_Name.c_str()), 1, &a_Value[0]);
        }
        void setVec2(const std::string& a_Name, float a_X, float a_Y) const
        {
            glUniform2f(glGetUniformLocation(ID, a_Name.c_str()), a_X, a_Y);
        }
        // ------------------------------------------------------------------------
        void setVec3(const std::string& a_Name, const glm::vec3& a_Value) const
        {
            glUniform3fv(glGetUniformLocation(ID, a_Name.c_str()), 1, &a_Value[0]);
        }
        void setVec3(const std::string& a_Name, float a_X, float a_Y, float a_Z) const
        {
            glUniform3f(glGetUniformLocation(ID, a_Name.c_str()), a_X, a_Y, a_Z);
        }
        // ------------------------------------------------------------------------
        void setVec4(const std::string& a_Name, const glm::vec4& a_Value) const
        {
            glUniform4fv(glGetUniformLocation(ID, a_Name.c_str()), 1, &a_Value[0]);
        }
        void setVec4(const std::string& a_Name, float a_X, float a_Y, float a_Z, float a_W) const
        {
            glUniform4f(glGetUniformLocation(ID, a_Name.c_str()), a_X, a_Y, a_Z, a_W);
        }
        // ------------------------------------------------------------------------
        void setMat2(const std::string& a_Name, const glm::mat2& a_Mat) const
        {
            glUniformMatrix2fv(glGetUniformLocation(ID, a_Name.c_str()), 1, GL_FALSE, &a_Mat[0][0]);
        }
        // ------------------------------------------------------------------------
        void setMat3(const std::string& a_Name, const glm::mat3& a_Mat) const
        {
            glUniformMatrix3fv(glGetUniformLocation(ID, a_Name.c_str()), 1, GL_FALSE, &a_Mat[0][0]);
        }
        // ------------------------------------------------------------------------
        void setMat4(const std::string& a_Name, const glm::mat4& a_Mat) const
        {
            glUniformMatrix4fv(glGetUniformLocation(ID, a_Name.c_str()), 1, GL_FALSE, &a_Mat[0][0]);
        }

    private:
        // utility function for checking shader compilation/linking errors.
        // ------------------------------------------------------------------------
        void checkCompileErrors(unsigned int a_Shader, std::string a_Type)
        {
            int success;
            char info_log[1024];
            if (a_Type != "PROGRAM")
            {
                glGetShaderiv(a_Shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(a_Shader, 1024, NULL, info_log);
                    std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << a_Type << "\n" << info_log << "\n -- --------------------------------------------------- -- " << std::endl;
                }
            }
            else
            {
                glGetProgramiv(a_Shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetProgramInfoLog(a_Shader, 1024, NULL, info_log);
                    std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << a_Type << "\n" << info_log << "\n -- --------------------------------------------------- -- " << std::endl;
                }
            }
        }
    };
};
#endif
