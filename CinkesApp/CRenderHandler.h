// ReSharper disable CppClangTidyCppcoreguidelinesSpecialMemberFunctions
#pragma once
#include "CCollisionShape.h"
#include "CCollisionObject.h"
#include "CRenderShape.h"
#include "CRenderWindow.h"
namespace Cinkes 
{

	struct CObjectWrapper {

		bool operator==(const CObjectWrapper& a_Rhs) {
			if (m_CollisionObject.get() == a_Rhs.m_CollisionObject.get() && m_RenderObject.get() == m_RenderObject.get())
			{
				return true;
			}
			return false;
		}


		std::shared_ptr<CCollisionObject> m_CollisionObject;
		std::shared_ptr<CRenderShape> m_RenderObject;

		void CreateRenderShape() {}
	};

	class CRenderHandler
	{
	public:
		CRenderHandler(bool a_CreateWindow)
		{
			m_Window = std::make_shared<CRenderWindow>();
			
			if (a_CreateWindow)
			{
				m_Window->InitializeWindow();
			}
		}
		~CRenderHandler() = default;

		bool RegisterObject(const std::shared_ptr<CCollisionObject>& a_Collision);
		void RegisterAll(const std::vector<std::shared_ptr<CCollisionObject>>& a_CollisionObjects); 
		// ReSharper disable once CppInconsistentNaming
		glm::mat4x4 ConvertTransformToGLM(const CTransform& a_Transform);
		glm::vec3 ConvertVectorToGlm(const CVector3& a_Vector3);

		void CreateWindowObject();

		bool RemoveWrapperByCollisionRef(std::shared_ptr<CCollisionObject>& a_Collision);
		bool RemoveWrapperByRenderRef(std::shared_ptr<CRenderShape>& a_Render);
		bool RemoveWrapperByRef(const CObjectWrapper& a_Wrapper);
		bool RemoveWrapperByIndex(int a_Index);

		CObjectWrapper GetWrapperByCollisionRef(std::shared_ptr<CCollisionObject>& a_Collision);
		CObjectWrapper GetWrapperByRenderRef(std::shared_ptr<CRenderShape>& a_Render);
		CObjectWrapper GetWrapperByIndex(int a_Index) { return m_Objects[a_Index]; }

		std::shared_ptr<CRenderWindow> m_Window;

	private:

		std::vector<CObjectWrapper> m_Objects;
	};
};
