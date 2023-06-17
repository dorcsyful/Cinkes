// ReSharper disable CppClangTidyCppcoreguidelinesPreferMemberInitializer
#include "CRigidBody.h"

#include <iostream>

#include "CBoxShape.h"
#include "CCollisionShape.h"
#include "CQuaternion.h"
#include "CUtils.h"


Cinkes::CRigidBody::CRigidBody(const CTransform& a_Transform, const std::shared_ptr<CCollisionShape>& a_CollisionShape, CScalar a_Mass, const CVector3& a_CenterOfMass)
{
	SetMass(a_Mass);
	m_CenterOfMass = a_CenterOfMass;
	m_Transform = a_Transform;
	m_Shape = a_CollisionShape;
	m_Moveable = true;
	m_Type = EOBJECT_TYPE::TYPE_RIGID;

}

Cinkes::CRigidBody::CRigidBody(CBody&& a_Rhs, const std::vector<std::shared_ptr<CSpring>>& a_AttachedSprings,
                               float a_Mass, CVector3 a_CenterOfMass): m_CenterOfMass(std::move(a_CenterOfMass))
{
	SetMass(a_Mass);
	m_Transform = a_Rhs.GetTransform();
	m_Shape = a_Rhs.GetCollisionShape();
	m_Moveable = true;
	m_Type = EOBJECT_TYPE::TYPE_RIGID;

}
Cinkes::CRigidBody::CRigidBody(CRigidBody&& a_Rhs) noexcept
{
	SetMass(a_Rhs.m_Mass);
	m_Transform = a_Rhs.GetTransform();
	m_Shape = a_Rhs.GetCollisionShape();
	m_Moveable = true;
	m_Type = EOBJECT_TYPE::TYPE_RIGID;

}

Cinkes::CRigidBody& Cinkes::CRigidBody::operator=(CRigidBody&& a_Rhs) noexcept  // NOLINT(bugprone-exception-escape)
{
		if (this == &a_Rhs) { return *this; }
	m_CenterOfMass = a_Rhs.GetCenterOfMass();
	SetMass(a_Rhs.m_Mass);
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
	SetMass(a_Rhs.m_Mass);

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
	// Calculate the diagonal elements of the inertia tensor
	CVector3 extents = static_cast<CBoxShape*>(m_Shape.get())->GetDimensions();
	CScalar diagX = 1 / (12 * m_Mass * (extents.getY() * extents.getY() + extents.getZ() * extents.getZ()));
	CScalar diagY = 1 / (12 * m_Mass * (extents.getX() * extents.getX() + extents.getZ() * extents.getZ()));
	CScalar diagZ = 1 / (12 * m_Mass * (extents.getX() * extents.getX() + extents.getY() * extents.getY()));

	// Create the diagonal matrix
	CMat3x3 diag(diagX, 0, 0,
		0, diagY, 0,
		0, 0, diagZ);

	// Calculate the inverse inertia tensor in the local space of the cuboid
	m_InverseIntertiaTensorLocal = diag;

	// Transform the inverse inertia tensor to the world space of the cuboid
	CMat3x3 rotation = GetTransform().getBasis();
	m_InverseIntertiaTensorWorld = rotation * m_InverseIntertiaTensorLocal * rotation.Transpose();

}

void Cinkes::CRigidBody::SetInertiaTensorLocal()
{
    /*m_InertiaTensorLocal = m_Shape->CalculateInertiaTensor(m_Mass);
	m_InverseIntertiaTensorLocal = m_InertiaTensorLocal.GetInverse();*/
}

void Cinkes::CRigidBody::AddForceAtPoint(const CVector3& a_ForceToAdd, const CVector3& a_Point)
{
	m_Force += a_ForceToAdd;
	CVector3 rel = (a_Point - GetTransform().getOrigin());
	m_Torque += a_ForceToAdd.Cross(rel);
}

void Cinkes::CRigidBody::Integrate(CScalar a_T)
{
	if (m_InverseMass < 0.001f)
		return;

	// Calculate linear acceleration from force inputs.
	m_LastFrameAcceleration = CVector3();
	m_LastFrameAcceleration += m_Force * m_InverseMass;

	// Calculate angular acceleration from torque inputs.
	CVector3 angularAcceleration =
		m_InverseIntertiaTensorWorld * (m_Torque);

	// Adjust velocities
	// Update linear velocity from both acceleration and impulse.
	m_Velocity += m_LastFrameAcceleration * a_T;

	// Update angular velocity from both acceleration and impulse.
	m_AngularVelocity += angularAcceleration * a_T;

	// Impose drag.
	m_Velocity *= CUtils::Pow(m_LinearDamping, a_T);
	m_AngularVelocity *= CUtils::Pow(m_AngularDamping, a_T);

	// Adjust positions
	// Update linear position.
	m_Transform.setOrigin(m_Transform.getOrigin() + m_Velocity * a_T);

	// Update angular position.
	CQuaternion q = m_Transform.getQuaternion();
	CVector3 temp = m_AngularVelocity * a_T;
	CQuaternion o = CQuaternion(temp[0], temp[1], temp[2], 0);
	o *= 0.5;
	q += o;
	m_Transform.setBasis(CMat3x3(q));

	// Normalise the orientation, and update the matrices with the new
	// position and orientation
	SetInverseInertiaTensorWorld();

	// Clear accumulators.
	ClearForces();

}

void Cinkes::CRigidBody::IntegratePosition(CScalar a_T)
{
	m_Transform.setOrigin(m_Transform.getOrigin() + m_Velocity * a_T);
}
