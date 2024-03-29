#pragma once
#include <cassert>
#include <map>
#include <string>
#include <vector>

#include "imgui.h"


namespace Cinkes
{
	enum EWIDGET_TYPE
	{
		EWIDGET_NOTYPE,
		EWIDGET_BUTTON,
		EWIDGET_CHECKBOX,
		EWIDGET_TEXT,
		EWIDGET_SLIDER,
		EWIDGET_NEWLINE
	};

	class CImguiWidget
	{
	public:
		virtual ~CImguiWidget() = default;;
		CImguiWidget(const char* a_Id) : m_Id(a_Id), m_Type(EWIDGET_NOTYPE) {}
		virtual void Draw();
		const char* m_Id;
		EWIDGET_TYPE m_Type;
	};
	class CButtonWidget : public CImguiWidget
	{
		CButtonWidget(const char* a_Id) : CImguiWidget(a_Id)
		{
			m_Id = a_Id; m_Type = EWIDGET_BUTTON; m_Pressed = false;
		}
		void Draw() override
		{
			ImGui::Button(m_Text.c_str());
		}
		std::string m_Text;
		bool m_Pressed;
	};
	class CCheckBoxWidget : public CImguiWidget
	{
		CCheckBoxWidget(const char* a_Id) : CImguiWidget(a_Id)
		{
			m_Id = a_Id; m_Type = EWIDGET_BUTTON; m_Pressed = false;
		}
		void Draw() override
		{
			ImGui::Button("Temp");
		}
		bool m_Pressed;
	};
	class CTextWidget : public CImguiWidget
	{
		CTextWidget(const char* a_Id) : CImguiWidget(a_Id)
		{
			m_Id = a_Id; m_Type = EWIDGET_BUTTON; m_Text = "";
		}
		void Draw() override
		{
			ImGui::Button("Temp");
		}
		const char* m_Text;
	};
	class CSliderWidget : public CImguiWidget
	{
		CSliderWidget(const char* a_Id) : CImguiWidget(a_Id)
		{
			m_Id = a_Id; m_Type = EWIDGET_BUTTON; m_Lower = 0.f; m_Upper = 0.f;
		}
		void Draw() override
		{
			ImGui::Button("Temp");
		}
		float m_Lower;
		float m_Upper;
	};
	class CNewLineWidget : public CImguiWidget
	{
		CNewLineWidget(const char* a_Id) : CImguiWidget(a_Id)
		{
			m_Id = a_Id; m_Type = EWIDGET_BUTTON;
		}
		void Draw() override
		{
			ImGui::Button("Temp");
		}
	};
	//This class adds and removes Imgui widgets as well as detects its input
	class CImguiHandler
	{
	public:
		CImguiHandler() = default;
		~CImguiHandler() = default;

		bool AddWidget(CImguiWidget& a_Widget, const std::string& a_WindowName)
		{
			for (const auto& widget : m_Widgets[a_WindowName])
			{
				if(a_Widget.m_Id == widget.m_Id)
				{
					assert(false);
					return false;
				}
			}
			m_Widgets[a_WindowName].push_back(a_Widget);
			return true;
		}

		bool RemoveWidget(const char* a_Id, const std::string& a_WindowName)
		{
			for (auto it = m_Widgets[a_WindowName].begin(); it != m_Widgets[a_WindowName].end(); ++it) {
				if (it->m_Id == a_Id) {
					m_Widgets[a_WindowName].erase(it);
					return true;
				}
			}
			assert(false);
			return false;
		}
		std::map<std::string, std::vector<CImguiWidget>> m_Widgets;
		std::map<std::string, std::vector<CImguiWidget>> m_ChangedState;
	};
}
