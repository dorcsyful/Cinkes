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
    if (a_Rhs > 0) {
        m_InverseMass = 1 / a_Rhs;
    }
    else { m_InverseMass = 0; }
	m_Mass = a_Rhs;
}

void Cinkes::CRigidBody::SetInverseInertiaTensorWorld()
{
    CTransform rotmat = GetTransform();
	//this is automatically generated code, I just made it compatible with mine
    CScalar t4 = rotmat.getBasis()[0][0] * m_InverseIntertiaTensor[0][0] +
        rotmat.getBasis()[1][0] * m_InverseIntertiaTensor[0][1] +
        rotmat.getBasis()[2][0] * m_InverseIntertiaTensor[0][2];
    CScalar t9 = rotmat.getBasis()[0][0] * m_InverseIntertiaTensor[1][0] +
        rotmat.getBasis()[1][0] * m_InverseIntertiaTensor[1][1] +
        rotmat.getBasis()[2][0] * m_InverseIntertiaTensor[1][2];
    CScalar t14 = rotmat.getBasis()[0][0] * m_InverseIntertiaTensor[2][0] +
        rotmat.getBasis()[1][0] * m_InverseIntertiaTensor[2][1] +
        rotmat.getBasis()[2][0] * m_InverseIntertiaTensor[2][2];
    CScalar t28 = rotmat.getBasis()[0][1] * m_InverseIntertiaTensor[0][0] +
        rotmat.getBasis()[1][1] * m_InverseIntertiaTensor[0][1] +
        rotmat.getBasis()[2][1] * m_InverseIntertiaTensor[0][2];
    CScalar t33 = rotmat.getBasis()[0][1] * m_InverseIntertiaTensor[1][0] +
        rotmat.getBasis()[1][1] * m_InverseIntertiaTensor[1][1] +
        rotmat.getBasis()[2][1] * m_InverseIntertiaTensor[1][2];
    CScalar t38 = rotmat.getBasis()[0][1] * m_InverseIntertiaTensor[2][0] +
        rotmat.getBasis()[1][1] * m_InverseIntertiaTensor[1][2] +
        rotmat.getBasis()[2][1] * m_InverseIntertiaTensor[2][2];
    CScalar t52 = rotmat.getBasis()[0][2] * m_InverseIntertiaTensor[0][0] +
        rotmat.getBasis()[2][2] * m_InverseIntertiaTensor[0][1] +
        rotmat.getBasis()[2][2] * m_InverseIntertiaTensor[0][2];
    CScalar t57 = rotmat.getBasis()[0][2] * m_InverseIntertiaTensor[1][0] +
        rotmat.getBasis()[1][2] * m_InverseIntertiaTensor[1][1] +
        rotmat.getBasis()[2][2] * m_InverseIntertiaTensor[1][2];
    CScalar t62 = rotmat.getBasis()[0][2] * m_InverseIntertiaTensor[2][0] +
        rotmat.getBasis()[1][2] * m_InverseIntertiaTensor[2][1] +
        rotmat.getBasis()[2][2] * m_InverseIntertiaTensor[2][2];

    m_InverseIntertiaTensorWorld[0][0] = t4 * rotmat.getBasis()[0][0] +
        t9 * rotmat.getBasis()[1][0] +
        t14 * rotmat.getBasis()[2][0];
    m_InverseIntertiaTensorWorld[1][0] = t4 * rotmat.getBasis()[0][1] +
        t9 * rotmat.getBasis()[1][1] +
        t14 * rotmat.getBasis()[2][1];
    m_InverseIntertiaTensorWorld[2][0] = t4 * rotmat.getBasis()[0][2] +
        t9 * rotmat.getBasis()[1][2] +
        t14 * rotmat.getBasis()[2][2];
    m_InverseIntertiaTensorWorld[0][1] = t28 * rotmat.getBasis()[0][0] +
        t33 * rotmat.getBasis()[1][0] +
        t38 * rotmat.getBasis()[2][0];
    m_InverseIntertiaTensorWorld[1][1] = t28 * rotmat.getBasis()[0][1] +
        t33 * rotmat.getBasis()[1][1] +
        t38 * rotmat.getBasis()[2][1];
    m_InverseIntertiaTensorWorld[2][1] = t28 * rotmat.getBasis()[0][2] +
        t33 * rotmat.getBasis()[1][2] +
        t38 * rotmat.getBasis()[2][2];
    m_InverseIntertiaTensorWorld[0][2] = t52 * rotmat.getBasis()[0][0] +
        t57 * rotmat.getBasis()[1][0] +
        t62 * rotmat.getBasis()[2][0];
    m_InverseIntertiaTensorWorld[1][2] = t52 * rotmat.getBasis()[0][1] +
        t57 * rotmat.getBasis()[1][1] +
        t62 * rotmat.getBasis()[2][1];
    m_InverseIntertiaTensorWorld[2][2] = t52 * rotmat.getBasis()[0][2] +
        t57 * rotmat.getBasis()[1][2] +
        t62 * rotmat.getBasis()[2][2];
}

void Cinkes::CRigidBody::Integrate(CScalar a_T)
{
    if (m_InverseMass < static_cast<CScalar>(0.001)) { return; }
	m_LastFrameAcceleration = m_Acceleration;
	m_LastFrameAcceleration += m_Force * m_InverseMass;

	CVector3 angularAcceleration = m_InverseIntertiaTensor * m_Torque;

	m_Velocity += m_LastFrameAcceleration * a_T;
	m_AngularVelocity += m_AngularAcceleration * a_T;

	m_Velocity *= CUtils::Pow(m_LinearDamping, a_T);
	m_AngularVelocity *= CUtils::Pow(m_AngularDamping, a_T);

	CQuaternion q = m_Transform.getQuaternion() + CVector3(angularAcceleration * a_T);
	CVector3 p = m_Transform.getOrigin() + m_Velocity * a_T;

    p *= CUtils::Pow(m_LinearDamping, a_T);
    q *= CUtils::Pow(m_AngularDamping, a_T);

	m_Transform = CTransform(CMat3x3(q), p);

	ClearForces();
}