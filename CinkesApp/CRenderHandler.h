#pragma once
#include "CCollisionShape.h"
#include "CCollisionObject.h"
#include "CRenderShape.h"
#include "CRenderWindow.h"
namespace Cinkes 
{

	struct CObjectWrapper {

		bool operator==(const CObjectWrapper a_Rhs) {
			if (m_CollisionObject.get() == a_Rhs.m_CollisionObject.get() && m_RenderObject.get() == m_RenderObject.get())
			{
				return true;
			}
			return false;
		}


		std::shared_ptr<CCollisionObject> m_CollisionObject;
		std::shared_ptr<CRenderShape> m_RenderObject;

		void CreateRenderShape();
		void RunVertexConverter();
		void ConvertBoxToVertices();
	};

	class CRenderHandler
	{
	public:
		CRenderHandler(bool a_CreateWindow);
		~CRenderHandler();

		bool RegisterObject(std::shared_ptr<CCollisionObject> a_Collision);
		//SLOW OPERATION! Recommended to only use it once! Allow duplicates for optimization.
		void RegisterAll(std::vector<std::shared_ptr<CCollisionObject>> a_CollisionObjects, bool a_DuplicatesAllowed); 
		void ConvertTransforms();

		void CreateWindowObject();
		void TerminateWindow();

		bool RemoveWrapperByCollisionRef(std::shared_ptr<CCollisionObject>& a_Collision);
		bool RemoveWrapperByRenderRef(std::shared_ptr<CRenderShape>& a_Render);
		bool RemoveWrapperByRef(CObjectWrapper a_Wrapper);
		bool RemoveWrapperByIndex(int a_Index);

		CObjectWrapper GetWrapperByCollisionRef(std::shared_ptr<CCollisionObject>& a_Collision);
		CObjectWrapper GetWrapperByRenderRef(std::shared_ptr<CRenderShape>& a_Render);
		CObjectWrapper GetWrapperByIndex(int a_Index) { return m_Objects[a_Index]; }

		/*Can be called from anywhere, if the project is set as a dependency.
		For best results create a (global) window object and pass it to the function.
		Otherwise the window will be closed and recreated every time the function is called*/
		static void DebugDraw(const std::vector<std::vector<CVector3>>& a_Vertices, const std::vector<std::vector<int>>& a_Indices,
			const std::vector<std::vector<CVector3>>& a_Normals, const std::vector<CTransform>& a_Transforms,
			float a_Wait = 5.f, CRenderWindow* a_Window = nullptr);

		std::shared_ptr<CRenderWindow> m_Window;

	private:

		std::vector<CObjectWrapper> m_Objects;
	};
};
