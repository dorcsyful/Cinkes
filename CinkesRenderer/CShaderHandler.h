#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>



class CShaderHandler
{
public:
	CShaderHandler() = default;
	~CShaderHandler() = default;

	bool CompileShaders();

	GLuint m_ShaderProgram;
	GLuint m_VertexShader;
	GLuint m_FragmentShader;
};

