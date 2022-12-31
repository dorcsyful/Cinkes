#pragma once
#include <vector>
#include <memory>
#include "CRenderDefines.h"
#include "CInputHandler.h"
#include "CRenderShape.h"

class GLFWwindow;

namespace Cinkes
{
	class CRenderWindow
	{
	public:
		CRenderWindow() { m_Input = std::make_shared<CInputHandler>(); };

		~CRenderWindow();

		bool InitializeWindow();
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
};
