// ReSharper disable CppClangTidyCppcoreguidelinesPreferMemberInitializer
#include "CRigidBody.h"

#include <iostream>

#include "CCollisionShape.h"
#include "CQuaternion.h"
#include "CUtils.h"


Cinkes::CRigidBody::CRigidBody(const CTransform& a_Transform, const std::shared_ptr<CCollisionShape>& a_CollisionShape, CScalar a_Mass, const CVector3& a_CenterOfMass)
{
	m_Mass = a_Mass;
	m_InverseMass = 1/a_Mass;
	m_CenterOfMass = a_CenterOfMass;
	m_Transform = a_Transform;
	m_Shape = a_CollisionShape;
	m_Moveable = true;
	m_Type = EOBJECT_TYPE::TYPE_RIGID;

}

Cinkes::CRigidBody::CRigidBody(CBody&& a_Rhs, const std::vector<std::shared_ptr<CSpring>>& a_AttachedSprings,
                               float a_Mass, CVector3 a_CenterOfMass): m_CenterOfMass(std::move(a_CenterOfMass))
{
	m_Mass = a_Mass;
	m_InverseMass = 1/a_Mass;
	m_Transform = a_Rhs.GetTransform();
	m_Shape = a_Rhs.GetCollisionShape();
	m_Moveable = true;
	m_Type = EOBJECT_TYPE::TYPE_RIGID;

}
Cinkes::CRigidBody::CRigidBody(CRigidBody&& a_Rhs) noexcept
{
	m_Mass = a_Rhs.m_Mass;
	m_Transform = a_Rhs.GetTransform();
	m_Shape = a_Rhs.GetCollisionShape();
	m_InverseMass = 1/m_Mass;
	m_Moveable = true;
	m_Type = EOBJECT_TYPE::TYPE_RIGID;

}

Cinkes::CRigidBody& Cinkes::CRigidBody::operator=(CRigidBody&& a_Rhs) noexcept  // NOLINT(bugprone-exception-escape)
{
		if (this == &a_Rhs) { return *this; }
	m_CenterOfMass = a_Rhs.GetCenterOfMass();
	m_InverseMass = a_Rhs.m_InverseMass;
	m_Transform = a_Rhs.GetTransform();
	m_Shape = a_Rhs.GetCollisionShape();
	m_Moveable = true;
	m_Type = EOBJECT_TYPE::TYPE_RIGID;

	return *this;
}

Cinkes::CRigidBody& Cinkes::CRigidBody::operator=(const CRigidBody& a_Rhs)
{
	if (this == &a_Rhs) { return *this; }
	m_CenterOfMass = a_Rhs.GetCenterOfMass();
	m_InverseMass = a_Rhs.m_InverseMass;

	m_Transform = a_Rhs.GetTransform();
	m_Shape = a_Rhs.GetCollisionShape();
	m_Moveable = true;
	m_Type = EOBJECT_TYPE::TYPE_RIGID;

	return *this;
}

void Cinkes::CRigidBody::SetMass(CScalar a_Rhs)
{
	if (a_Rhs > 0) {
		m_InverseMass = 1 / a_Rhs;
	}
	else { m_InverseMass = 0; }
	m_Mass = a_Rhs;
}


Cinkes::CMat3x3 Cinkes::CRigidBody::GetInertiaTensorLocal()
{
	if (m_InertiaTensorLocal == CMat3x3::GetIdentity())
	{
		m_InertiaTensorLocal = m_Shape->CalculateInertiaTensor(m_Mass);
	}
	return m_InertiaTensorLocal;
}

Cinkes::CMat3x3 Cinkes::CRigidBody::GetInverseInertiaTensorLocal()
{
	if (m_InverseIntertiaTensorLocal == CMat3x3::GetIdentity())
	{
		m_InertiaTensorLocal = m_Shape->CalculateInertiaTensor(m_Mass);
		m_InverseIntertiaTensorLocal = m_InertiaTensorLocal.GetInverse();
	}
	return m_InverseIntertiaTensorLocal;
}

Cinkes::CMat3x3 Cinkes::CRigidBody::GetInverseInertiaTensorWorld()
{
	if (m_InverseIntertiaTensorWorld == CMat3x3::GetIdentity())
	{
		m_InertiaTensorLocal = m_Shape->CalculateInertiaTensor(m_Mass);
		m_InverseIntertiaTensorLocal = m_InertiaTensorLocal.GetInverse();
		SetInverseInertiaTensorWorld();
	}
	return m_InverseIntertiaTensorLocal;
}

void Cinkes::CRigidBody::SetInverseInertiaTensorWorld()
{
	CMat3x3 transposed = GetTransform().getBasis().Transpose();
	CVector3 temp = CVector3(m_InverseIntertiaTensorLocal[0][0], m_InverseIntertiaTensorLocal[1][1], m_InverseIntertiaTensorLocal[2][2]);
	m_InverseIntertiaTensorWorld = GetTransform().getBasis().Scale(temp) * transposed;
}

void Cinkes::CRigidBody::SetInertiaTensorLocal()
{
    m_InertiaTensorLocal = m_Shape->CalculateInertiaTensor(m_Mass);
	m_InverseIntertiaTensorLocal = m_InertiaTensorLocal.GetInverse();
}

void Cinkes::CRigidBody::AddForceAtPoint(const CVector3& a_ForceToAdd, const CVector3& a_Point)
{
	m_Force += a_ForceToAdd;
	CVector3 rel = (a_Point - GetTransform().getOrigin());
	m_Torque += rel.Cross(a_ForceToAdd);
}

void Cinkes::CRigidBody::Integrate(CScalar a_T)
{
    if (m_InverseMass < static_cast<CScalar>(0.001)) { return; }
    m_Velocity += m_Force  * m_InverseMass * a_T;
	m_AngularVelocity += m_InverseIntertiaTensorWorld * m_Torque * a_T;
	m_Velocity *= m_LinearDamping;
	m_AngularVelocity *= m_AngularDamping;
    SetInverseInertiaTensorWorld();
	ClearForces();
}

void Cinkes::CRigidBody::IntegratePosition(CScalar a_T)
{
	m_Transform.setOrigin(m_Transform.getOrigin() + m_Velocity * a_T);
}
