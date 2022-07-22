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
}

Cinkes::CRigidBody::CRigidBody(CBody&& a_Rhs, const std::vector<std::shared_ptr<CSpring>>& a_AttachedSprings,
                               float a_Mass, CVector3 a_CenterOfMass): m_CenterOfMass(std::move(a_CenterOfMass))
{
	m_Mass = a_Mass;
	m_InverseMass = 1/a_Mass;
	m_Transform = a_Rhs.GetTransform();
	m_Shape = a_Rhs.GetCollisionShape();
	m_Moveable = true;

}
Cinkes::CRigidBody::CRigidBody(CRigidBody&& a_Rhs) noexcept
{
	m_Mass = a_Rhs.m_Mass;
	m_Transform = a_Rhs.GetTransform();
	m_Shape = a_Rhs.GetCollisionShape();
	m_InverseMass = 1/m_Mass;
	m_Moveable = true;

}

Cinkes::CRigidBody& Cinkes::CRigidBody::operator=(CRigidBody&& a_Rhs) noexcept  // NOLINT(bugprone-exception-escape)
{
		if (this == &a_Rhs) { return *this; }
	m_CenterOfMass = a_Rhs.GetCenterOfMass();
	m_InverseMass = a_Rhs.m_InverseMass;
	m_Transform = a_Rhs.GetTransform();
	m_Shape = a_Rhs.GetCollisionShape();
	m_Moveable = true;

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

void Cinkes::CRigidBody::SetInverseInertiaTensorWorld()
{
	CMat3x3 transposed = GetTransform().getBasis().Transpose();
	CVector3 temp = CVector3(m_InverseIntertiaTensor[0][0], m_InverseIntertiaTensor[1][1], m_InverseIntertiaTensor[2][2]);
	m_InverseIntertiaTensorWorld = GetTransform().getBasis().Scale(temp) * transposed;
}

void Cinkes::CRigidBody::SetInverseInertiaTensor()
{
    CMat3x3 inertia = m_Shape->CalculateInertiaTensor(m_Mass);
    CVector3 temp = CVector3(inertia[0][0] != CScalar(0.0) ? CScalar(1.0) / inertia[0][0] : CScalar(0.0),
        inertia[1][1] != CScalar(0.0) ? CScalar(1.0) / inertia[1][1] : CScalar(0.0),
        inertia[2][2] != CScalar(0.0) ? CScalar(1.0) / inertia[2][2] : CScalar(0.0));
    m_InverseIntertiaTensor[0][0] = temp.getX();
    m_InverseIntertiaTensor[1][1] = temp.getY();
    m_InverseIntertiaTensor[2][2] = temp.getZ();
}

void Cinkes::CRigidBody::Integrate(CScalar a_T)
{


    if (m_InverseMass < static_cast<CScalar>(0.001)) { return; }
    m_Velocity += m_Force * a_T * m_InverseMass;
	m_AngularVelocity += m_InverseIntertiaTensorWorld * m_Torque * a_T;

	m_Velocity *= m_LinearDamping;
	m_AngularVelocity *= m_AngularDamping;
    SetInverseInertiaTensor();
    SetInverseInertiaTensorWorld();
	ClearForces();
}