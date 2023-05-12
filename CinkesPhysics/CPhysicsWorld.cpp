#include "CPhysicsWorld.h"

#include <iostream>

#include "CForceGeneratorRegistry.h"
#include "CGravitiyGenerator.h"
#include "CRigidBody.h"

void Cinkes::CPhysicsWorld::Update(CScalar a_T)
{

	RunCollision(a_T);
	if (!m_Contacts.empty()) {
	}
	m_FGenerators->UpdateGenerators();


	for (const auto& element : m_RigidBodies)
	{
		element->Integrate(a_T);
		
	}	
	for (const auto& element : m_RigidBodies)
	{
		CTransform trans = CTransform(UpdateRotation(element->GetAngularVelocity(), element->GetTransform().getBasis(), a_T),
			element->GetTransform().getOrigin() + element->GetLinearVelocity() * a_T);
		element->SetTransform(trans);

	}
}

Cinkes::CMat3x3 Cinkes::CPhysicsWorld::UpdateRotation(const CVector3& a_Velocity, const CMat3x3& a_Initial, CScalar a_T) {
	// Calculate the rotation matrix based on the current angular velocity
	CMat3x3 rotation_delta;
	CScalar angle = CUtils::Sqrt(a_Velocity[0] * a_Velocity[0] +
		a_Velocity[1] * a_Velocity[1] +
		a_Velocity[2] * a_Velocity[2]);
	if (angle > 0.0) {
		CScalar axis_x = a_Velocity[0] / angle;
		CScalar axis_y = a_Velocity[1] / angle;
		CScalar axis_z = a_Velocity[2] / angle;
		CScalar cos_angle = CUtils::Cos(angle * a_T);
		CScalar sin_angle = CUtils::Sin(angle * a_T);
		rotation_delta[0][0] = cos_angle + axis_x * axis_x * (1 - cos_angle);
		rotation_delta[0][1] = axis_x * axis_y * (1 - cos_angle) - axis_z * sin_angle;
		rotation_delta[0][2] = axis_x * axis_z * (1 - cos_angle) + axis_y * sin_angle;
		rotation_delta[1][0] = axis_y * axis_x * (1 - cos_angle) + axis_z * sin_angle;
		rotation_delta[1][1] = cos_angle + axis_y * axis_y * (1 - cos_angle);
		rotation_delta[1][2] = axis_y * axis_z * (1 - cos_angle) - axis_x * sin_angle;
		rotation_delta[2][0] = axis_z * axis_x * (1 - cos_angle) - axis_y * sin_angle;
		rotation_delta[2][1] = axis_z * axis_y * (1 - cos_angle) + axis_x * sin_angle;
		rotation_delta[2][2] = cos_angle + axis_z * axis_z * (1 - cos_angle);
	}
	else {
		rotation_delta = { {1.0, 0.0, 0.0},
						 {0.0, 1.0, 0.0},
						 {0.0, 0.0, 1.0} };
	}

	// Apply the rotation delta to the rotation matrix
	CMat3x3 new_rotation;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			CScalar sum = 0.0;
			for (int k = 0; k < 3; k++) {
				sum += rotation_delta[i][k] * a_Initial[k][j];
			}
			new_rotation[i][j] = sum;
		}
	}
	return new_rotation;
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

bool Cinkes::CPhysicsWorld::AddSpring(const std::shared_ptr<CSpring>& a_Spring)
{
	if (std::find(m_Springs.begin(), m_Springs.end(), a_Spring) != m_Springs.end()) { return false; }
	m_Springs.push_back(a_Spring);
	m_FGenerators->GetGeneratorByType(EGENERATOR_TYPE::TYPE_SPRING_BASIC)->AddObject(m_Springs[m_Springs.size() - 1].get());
	return true;
}
