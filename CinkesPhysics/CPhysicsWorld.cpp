#include "CPhysicsWorld.h"
#include "CForceGenerator.h"
Cinkes::CPhysicsWorld::CPhysicsWorld()
{
	m_FGenerators.push_back(std::make_shared<CForceGenerator>());
}
void Cinkes::CPhysicsWorld::Update(CScalar a_T)
{
}
void Cinkes::CPhysicsWorld::Integrate(const std::shared_ptr<CRigidBody>& a_RigidBody)
{
}

bool Cinkes::CPhysicsWorld::RemoveSpringByIndex(int a_Index, bool a_Delete)
{
	if(static_cast<unsigned>(a_Index) < m_Springs.size())
	{
		
	}
	return false;
}

bool Cinkes::CPhysicsWorld::RemoveSpringByType(int a_Index, bool a_Delete)
{
	return false;
}

bool Cinkes::CPhysicsWorld::AddGenerator(const std::shared_ptr<CForceGenerator>& a_Generator)
{
	return false;
}

bool Cinkes::CPhysicsWorld::RemoveGeneratorByValue(const std::shared_ptr<CForceGenerator>& a_Generator, bool a_Delete)
{
	return false;
}

bool Cinkes::CPhysicsWorld::RemoveGeneratorByIndex(int a_Index, bool a_Delete)
{
	return false;
}

bool Cinkes::CPhysicsWorld::AddRigidBody(const std::shared_ptr<CRigidBody>& a_Generator)
{
	return false;
}

bool Cinkes::CPhysicsWorld::RemoveRigidBodyByValue(const std::shared_ptr<CRigidBody>& a_Generator, bool a_Delete)
{
	return false;
}
