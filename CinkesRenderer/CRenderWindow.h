#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "CShader.h"
#include "CRenderShape.h"
#include "CTexture.h"

#include "CInputHandler.h"

class CRenderWindow
{
public:
	CRenderWindow() { m_Input = std::make_shared<CInputHandler>(); };
	CRenderWindow(int a_Width, int a_Height, int a_Version_Major = 4, int a_Version_Minor = 6);

	~CRenderWindow();

	bool InitializeWindow(int a_Width, int a_Height, int a_Version_Major, int a_Version_Minor);
	void Run();
	void Update();

	bool AddRenderShape(std::shared_ptr<CRenderShape>& a_Shape);
	bool RemoveRenderShapeByObject(std::shared_ptr<CRenderShape>& a_Shape);
	bool RemoveRenderShapeByIndex(unsigned int a_Index);

	std::vector<std::shared_ptr<CRenderShape>> m_Shapes;
	std::shared_ptr<CShader> m_Shader;
	GLFWwindow* m_Window = nullptr;
	std::shared_ptr<CInputHandler> m_Input;

};

