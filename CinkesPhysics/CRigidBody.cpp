#include "CRigidBody.h"

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
	m_InverseMass = 1/a_Rhs;
	m_Mass = a_Rhs;
}

void Cinkes::CRigidBody::Integrate(CScalar a_T)
{
	m_LastFrameAcceleration = m_Acceleration;
	m_LastFrameAcceleration += m_Force * m_InverseMass;

	CVector3 angularAcceleration = m_InverseIntertiaTensor * m_Force;

	m_Velocity += m_LastFrameAcceleration * a_T;
	m_AngularVelocity += m_AngularAcceleration * a_T;

	m_Velocity *= CUtils::Pow(m_LinearDamping, a_T);
	m_AngularVelocity *= CUtils::Pow(m_AngularDamping, a_T);

	CQuaternion q = m_Transform.getQuaternion() + CVector3(angularAcceleration * a_T);
	CVector3 p = m_Transform.getOrigin() + m_Velocity * a_T;

	m_Transform = CTransform(CMat3x3(q), p);

	ClearForces();
}