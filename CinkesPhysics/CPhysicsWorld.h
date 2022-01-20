#pragma once
#include "../CinkesCollision/CCollisionWorld.h"

namespace Cinkes
{
	class CForceGenerator;
	class CSprings;
	class CRigidBody;

	class CPhysicsWorld : public CCollisionWorld
	{
	public:
		CPhysicsWorld();

		void Integrate(const std::shared_ptr<CRigidBody>& a_RigidBody);
		void Update(CScalar a_T);

		
		bool AddGenerator(const std::shared_ptr<CForceGenerator>& a_Generator);
		bool RemoveGeneratorByValue(const std::shared_ptr<CForceGenerator>& a_Generator, bool a_Delete);
		bool RemoveGeneratorByIndex(int a_Index, bool a_Delete);

		bool AddRigidBody(const std::shared_ptr<CRigidBody>& a_Generator);
		bool RemoveRigidBodyByValue(const std::shared_ptr<CRigidBody>& a_Generator, bool a_Delete);
		bool RemoveRigidBodyByIndex(int a_Index, bool a_Delete);

		bool AddSpring(const std::shared_ptr<CForceGenerator>& a_Generator);
		bool RemoveSpringByValue(const std::shared_ptr<CForceGenerator>& a_Generator, bool a_Delete);
		bool RemoveSpringByIndex(int a_Index, bool a_Delete);
		bool RemoveSpringByType(int a_Index, bool a_Delete);

	private:
		std::vector<std::shared_ptr<CForceGenerator>> m_FGenerators;
		std::vector<std::shared_ptr<CSprings>> m_Springs;
		std::vector<std::shared_ptr<CRigidBody>> m_RigidBodies;
	};


}
