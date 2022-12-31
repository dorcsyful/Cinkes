#include "CShaderHandler.h"
#include <iostream>
const char* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

bool CShaderHandler::CompileShaders()
{
    std::cout << "hgfds";
    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_VertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(m_VertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_VertexShader, 512, NULL, infoLog);
        std::cout << "Cannot compile vertex shader!";
        return false;
    }
    // fragment shader
    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_FragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(m_FragmentShader);
    // check for shader compile errors
    glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_FragmentShader, 512, NULL, infoLog);
        std::cout << "Cannot compile fragment shader!";
        return false;
    }
    // link shaders
    m_ShaderProgram = glCreateProgram();
    glAttachShader(m_ShaderProgram, m_VertexShader);
    glAttachShader(m_ShaderProgram, m_FragmentShader);
    glLinkProgram(m_ShaderProgram);
    // check for linking errors
    glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ShaderProgram, 512, NULL, infoLog);
        std::cout << "Linking failed!";
        return false;
    }
    std::cout << success << std::endl;

    glDeleteShader(m_VertexShader);
    glDeleteShader(m_FragmentShader);
    return true;
}
