#pragma once
#include <string>
#include <vector>
#include <glm/vec3.hpp>
#include "CRenderWindow.h"
#include "CRenderDefines.h"
namespace Cinkes
{
	class CVector3;

    enum class EVISUALIZER_TYPE
    {
	    TYPE_NONE,
        TYPE_GJK,
        TYPE_EPA
    };

    class CDebugVisualization
    {
    public:
	    virtual ~CDebugVisualization() = default;
	    CDebugVisualization() { m_Type = EVISUALIZER_TYPE::TYPE_NONE; }
        virtual bool Display() = 0;
        EVISUALIZER_TYPE m_Type;
        std::vector<std::shared_ptr<CRenderShape>> m_OutShapes;
    };

	class CEPAVisualization : public CDebugVisualization {
	public:
        CEPAVisualization() { m_Type = EVISUALIZER_TYPE::TYPE_EPA; }
        bool Display() override;
        bool AddEntry(float a_X, float a_Y, float a_Z, const std::vector<int>& a_Indices, size_t a_Closest)
        {
            m_Points.emplace_back(a_X, a_Y, a_Z);
            m_Indices.push_back(a_Indices);
            m_ClosestIndex.push_back(a_Closest);

            return true;
        }
		std::vector<glm::vec3> m_Points;
		std::vector<std::vector<int>> m_Indices;
		std::vector<size_t> m_ClosestIndex;
	};

    class CGJKVisualization : public CDebugVisualization
    {
    public:
        CGJKVisualization() { m_Type = EVISUALIZER_TYPE::TYPE_GJK; }
        bool Display() override;
        void AddEntry(float a_X, float a_Y, float a_Z)
        {
            m_Simplex.emplace_back(a_X, a_Y, a_Z);
        }
        std::vector<glm::vec3> m_Simplex;
    };



    class CDebugDrawer
    {


    public:

        CDebugDrawer(const CDebugDrawer& a_Other) = delete;
        CDebugDrawer(CDebugDrawer&& a_Other) = default;

        void operator=(const CDebugDrawer&) = delete;
        CDebugDrawer& operator=(CDebugDrawer&& a_Rhs) = default;

        static CDebugDrawer* GetInstance(const std::string& a_Value = "Test");

        void Draw(CDebugVisualization* a_Visualizer)
        {
            a_Visualizer->Display();
            for(auto& current : a_Visualizer->m_OutShapes)
            {
                current->LoadTexture(TEXTURE, m_Window->m_Shader.get());
                m_Window->AddRenderShape(current);
            }
            m_Window->Run();
        }

        std::string Value() const {
            return m_Value;
        }

        //Make sure the window passed is already created! 
        void SetRenderWindow(std::shared_ptr<CRenderWindow>& a_Window)
        {
            assert(a_Window->m_Window != nullptr);
            m_Window = a_Window;
            
        } 

        std::shared_ptr<CRenderWindow> m_Window;
    private:
        explicit CDebugDrawer(std::string a_Value) : m_Window(nullptr), m_Value(std::move(a_Value))
        {
        }

        ~CDebugDrawer() = default;
        static CDebugDrawer* m_Debugger;

        std::string m_Value;

    };


    inline CDebugDrawer* CDebugDrawer::GetInstance(const std::string& a_Value)
    {

        if (m_Debugger == nullptr) {
            m_Debugger = new CDebugDrawer(a_Value);
        }
        return m_Debugger;
    }
}

