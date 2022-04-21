#include "CPhysicsWorld.h"

#include <iostream>

#include "CForceGeneratorRegistry.h"
#include "CGravitiyGenerator.h"
#include "CRigidBody.h"

void Cinkes::CPhysicsWorld::Update(CScalar a_T)
{
	m_FGenerators->UpdateGenerators();

	for (const auto& element : m_RigidBodies)
	{
		element->Integrate(a_T);
		
	}
	RunCollision(a_T);
	if (!m_Contacts.empty()) {
		m_TestResolver->Resolve(m_Contacts, a_T);
	}
	for (const auto& element : m_RigidBodies)
	{
		element->SetTransform(CTransform(CMat3x3(), element->GetTransform().getOrigin() + element->GetLinearVelocity() * a_T));

	}
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
	if (std::find(m_RigidBodies.begin(), m_RigidBodies.end(), a_Body) != m_RigidBodies.end()) { return false; }
	m_RigidBodies.push_back(a_Body);
	auto a = std::static_pointer_cast<CCollisionObject>(a_Body);
	AddObject(a);
	m_FGenerators->GetGeneratorByType(EGENERATOR_TYPE::TYPE_GRAVITY)->AddObject(m_RigidBodies[m_RigidBodies.size() - 1].get());
	return true;
}

bool Cinkes::CPhysicsWorld:: RemoveRigidBodyByValue(const std::shared_ptr<CRigidBody>& a_Body, bool a_Delete)
{
	auto it = std::find(m_RigidBodies.begin(), m_RigidBodies.end(), a_Body);
	if (it == m_RigidBodies.end()) { return false; }
	m_RigidBodies.erase(it);
	if(a_Delete)
	{
		RemoveObject(std::static_pointer_cast<CCollisionObject>(a_Body));
		a_Body->m_InRemoveQueue = true;
	}

	return true;
}

bool Cinkes::CPhysicsWorld::RemoveRigidBodyByIndex(int a_Index)
{
	m_RigidBodies[a_Index]->m_InRemoveQueue = true;
	CRigidBody* rigid = m_RigidBodies[a_Index].get();
	if(m_RigidBodies.erase(std::find(m_RigidBodies.begin(),m_RigidBodies.end(),m_RigidBodies[a_Index])) != m_RigidBodies.end())
	{
		return false;
	}
	return true;
}
