#pragma once
#include <map>
#include <vector>
#include <memory>

#include "CImguiHandler.h"
#include "CRenderDefines.h"
#include "CInputHandler.h"
#include "CRenderShape.h"

struct GLFWwindow;

namespace Cinkes
{
	class CRenderWindow
	{
	public:
		CRenderWindow()
		{
			m_Input = std::make_shared<CInputHandler>();
			m_Imgui = std::make_shared<CImguiHandler>();

		}

		~CRenderWindow();

		bool InitializeWindow();
		void Update();


		bool AddRenderShape(std::shared_ptr<CRenderShape>& a_Shape);
		bool AddLine(std::shared_ptr<CLineRendered>& a_Lines);
		bool AddLine(const glm::vec3& a_Start, const glm::vec3& a_End, const glm::vec3& a_Color);
		bool RemoveRenderShapeByObject(std::shared_ptr<CRenderShape>& a_Shape);
		bool RemoveRenderShapeByIndex(unsigned int a_Index);
		bool AddShader(const char* a_ShaderName, const char* a_VertexPath, const char* a_FragmentPath);
		bool RenderUpdate();

		std::map<const char*, std::vector< std::shared_ptr<CRenderShape> > > m_Shapes;
		std::map<const char*, std::shared_ptr<CShader>> m_Shader;
		std::vector<std::shared_ptr<CLineRendered>> m_Lines;
		GLFWwindow* m_Window = nullptr;
		std::shared_ptr<CInputHandler> m_Input;
		std::shared_ptr<CImguiHandler> m_Imgui;

	};
};
