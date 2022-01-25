#include "CRigidBody.h"


Cinkes::CRigidBody::CRigidBody(const CTransform& a_Transform, const std::shared_ptr<CBody>& a_CollisionShape, const std::vector<std::shared_ptr<CSpring>>& a_AttachedSprings, CScalar a_Mass, const CVector3& a_CenterOfMass)
{
	m_Mass = a_Mass;
	m_CenterOfMass = a_CenterOfMass;
	m_AttachedSprings = a_AttachedSprings;
	m_Transform = a_Transform;
	m_Shape = a_CollisionShape->GetCollisionShape();
	m_Moveable = true;
}

Cinkes::CRigidBody::CRigidBody(CBody&& a_Rhs, const std::vector<std::shared_ptr<CSpring>>& a_AttachedSprings,
                               float a_Mass, CVector3 a_CenterOfMass): m_CenterOfMass(std::move(a_CenterOfMass))
{
	m_Mass = a_Mass;
	m_AttachedSprings = a_AttachedSprings;
	m_Transform = a_Rhs.GetTransform();
	m_Shape = a_Rhs.GetCollisionShape();
	m_Moveable = true;

}
Cinkes::CRigidBody::CRigidBody(CRigidBody&& a_Rhs) noexcept
{
	m_Transform = a_Rhs.GetTransform();
	m_Shape = a_Rhs.GetCollisionShape();
	m_Mass = 0;
	m_Moveable = true;

}

Cinkes::CRigidBody& Cinkes::CRigidBody::operator=(CRigidBody&& a_Rhs) noexcept  // NOLINT(bugprone-exception-escape)
{
		if (this == &a_Rhs) { return *this; }
	m_CenterOfMass = a_Rhs.GetCenterOfMass();
	m_Mass = a_Rhs.m_Mass;
	m_AttachedSprings = a_Rhs.m_AttachedSprings;
	m_Transform = a_Rhs.GetTransform();
	m_Shape = a_Rhs.GetCollisionShape();
	m_Moveable = true;

	return *this;
}

Cinkes::CRigidBody& Cinkes::CRigidBody::operator=(const CRigidBody& a_Rhs)
{
	if (this == &a_Rhs) { return *this; }
	m_CenterOfMass = a_Rhs.GetCenterOfMass();
	m_Mass = a_Rhs.m_Mass;
	m_AttachedSprings = a_Rhs.m_AttachedSprings;
	m_Transform = a_Rhs.GetTransform();
	m_Shape = a_Rhs.GetCollisionShape();
	m_Moveable = true;

	return *this;
}

std::vector<std::shared_ptr<Cinkes::CSpring>> Cinkes::CRigidBody::GetAllSprings()
{
	return m_AttachedSprings;
}

std::vector<std::shared_ptr<Cinkes::CSpring>> Cinkes::CRigidBody::GetSpringsByType(ESPRING_TYPE a_Type)
{
	std::vector<std::shared_ptr<CSpring>> returnValue;
	for(auto& current : m_AttachedSprings)
	{
		if(current->GetType() == a_Type)
		{
			returnValue.push_back(current);
		}
	}
	return returnValue;
}

float Cinkes::CRigidBody::GetMass()
{
	return m_Mass;
}

CScalar Cinkes::CRigidBody::GetMass() const
{
	return m_Mass;
}

void Cinkes::CRigidBody::SetMass(CScalar a_Rhs)
{
	m_Mass = 1/a_Rhs;
}

Cinkes::CVector3 Cinkes::CRigidBody::GetCenterOfMass()
{
	return m_CenterOfMass;
}

Cinkes::CVector3 Cinkes::CRigidBody::GetCenterOfMass() const
{
	return m_CenterOfMass;
}

void Cinkes::CRigidBody::SetCenterOfMass(const CVector3& a_Rhs)
{
	m_CenterOfMass = a_Rhs;
}

