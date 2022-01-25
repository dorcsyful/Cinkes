#include "CPhysicsWorld.h"

#include <iostream>

#include "CForceGeneratorRegistry.h"
#include "CGravitiyGenerator.h"
#include "CRigidBody.h"

void Cinkes::CPhysicsWorld::Update(CScalar a_T)
{
	RunCollision(a_T);
	for (const auto& element : m_RigidBodies)
	{
		Integrate(element, a_T);
	}
}

void Cinkes::CPhysicsWorld::Integrate(const std::shared_ptr<CRigidBody>& a_RigidBody, CScalar a_T)
{
	for (auto element : a_RigidBody->GetAllGenerators())
	{
		element->UpdateForce(a_RigidBody.get(), a_T);
	}
	std::cout << "Force affecting: " << a_RigidBody->GetForce().getX() << " " << a_RigidBody->GetForce().getY() << " " << a_RigidBody->GetForce().getZ() << std::endl;

	CVector3 position = a_RigidBody->GetTransform().getOrigin() + (a_RigidBody->GetForce() * a_T);
	a_RigidBody->SetTransform(CTransform(CMat3x3(),position));
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

bool Cinkes::CPhysicsWorld::AddRigidBody(const std::shared_ptr<CRigidBody>& a_Body)
{
	if (std::find(m_RigidBodies.begin(), m_RigidBodies.end(), a_Body) == m_RigidBodies.end()) { return false; }
	m_RigidBodies.push_back(a_Body);
	auto a = std::static_pointer_cast<CCollisionObject>(a_Body);
	AddObject(a);
	m_RigidBodies[m_RigidBodies.size() - 1]->AddGenerator(m_FGenerators->GetGeneratorByType(EGENERATOR_TYPE::TYPE_GRAVITY));
	return true;
}

bool Cinkes::CPhysicsWorld::RemoveRigidBodyByValue(const std::shared_ptr<CRigidBody>& a_Body, bool a_Delete)
{
	auto it = std::find(m_RigidBodies.begin(), m_RigidBodies.end(), a_Body);
	if (it == m_RigidBodies.end()) { return false; }
	m_RigidBodies.erase(it);
	if(a_Delete)
	{
		RemoveObject(std::static_pointer_cast<CCollisionObject>(a_Body));
		delete std::get_deleter<CRigidBody>(a_Body);
	}

	return true;
}

bool Cinkes::CPhysicsWorld::RemoveRigidBodyByIndex(int a_Index, bool a_Delete)
{
	CRigidBody* rigid = m_RigidBodies[a_Index].get();
	if(m_RigidBodies.erase(std::find(m_RigidBodies.begin(),m_RigidBodies.end(),m_RigidBodies[a_Index])) != m_RigidBodies.end())
	{
		return false;
	}
	if(a_Delete)
	{
		delete rigid;
	}
	return true;
}
