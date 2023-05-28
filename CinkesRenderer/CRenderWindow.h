#pragma once
#include <map>
#include <vector>
#include <memory>

#include "CRenderDefines.h"
#include "CInputHandler.h"
#include "CRenderShape.h"
#include "CLightShape.h"
struct GLFWwindow;

namespace Cinkes
{
	class CRenderWindow
	{
	public:
		CRenderWindow()
		{
			m_Input = std::make_shared<CInputHandler>();

		}

		~CRenderWindow();

		bool InitializeWindow();
		void Update();


		bool AddRenderShape(std::shared_ptr<CRenderShape>& a_Shape);
		bool AddLine(std::shared_ptr<CLineRendered>& a_Lines);
		bool AddLine(const glm::vec3& a_Start, const glm::vec3& a_End, const glm::vec3& a_Color);
		bool RemoveRenderShapeByObject(std::shared_ptr<CRenderShape>& a_Shape);
		bool RemoveRenderShapeByIndex(unsigned int a_Index);
		bool RenderUpdate();
		void CreateMaterial(const glm::vec3& a_BaseColor, const std::string& a_BaseTexturePath = "");

		std::vector<std::shared_ptr<CRenderShape>> m_Shapes;
		std::vector < std::shared_ptr<CLightShape>> m_Lights;
		std::vector<std::shared_ptr<CLineRendered>> m_Lines;
		std::map<std::string, std::shared_ptr<CShader>> m_Shaders;
		GLFWwindow* m_Window = nullptr;
		std::shared_ptr<CInputHandler> m_Input;

	};
};
