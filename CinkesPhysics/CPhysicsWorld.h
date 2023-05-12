#pragma once
#include "CForceGeneratorRegistry.h"
#include "CCollisionResolver.h"
#include "CCollisionWorld.h"


namespace Cinkes
{
	class CSprings;
	class CRigidBody;

	class CPhysicsWorld : public CCollisionWorld
	{
	public:
		CPhysicsWorld() {
			m_FGenerators = std::make_shared<CForceGeneratorRegistry>();
			m_Resolver = std::make_shared<CCollisionResolver>();
		}
		~CPhysicsWorld() = default;
		void Update(CScalar a_T);

		bool AddRigidBody(const std::shared_ptr<CRigidBody>& a_Body);
		bool RemoveRigidBodyByValue(const std::shared_ptr<CRigidBody>& a_Body, bool a_Delete);
		bool RemoveRigidBodyByIndex(int a_Index);

		bool AddSpring(const std::shared_ptr<CSpring>& a_Spring);
		bool RemoveSpringByValue(const std::shared_ptr<CForceGenerator>& a_Generator, bool a_Delete) { return false; }
		bool RemoveSpringByIndex(int a_Index, bool a_Delete);
		bool RemoveSpringByType(int a_Index, bool a_Delete);

		std::vector<std::shared_ptr<CRigidBody>> GetAllRigidBodies() const { return m_RigidBodies; }
		CForceGeneratorRegistry* GetGeneratorRegistry() const { return m_FGenerators.get(); }

	private:
		CMat3x3 UpdateRotation(const CVector3& a_Velocity, const CMat3x3& a_Initial, CScalar a_T);

		std::shared_ptr<CForceGeneratorRegistry> m_FGenerators;
		std::vector<std::shared_ptr<CSpring>> m_Springs;
		std::vector<std::shared_ptr<CRigidBody>> m_RigidBodies;
		std::shared_ptr<CCollisionResolver> m_Resolver;
	};


}
