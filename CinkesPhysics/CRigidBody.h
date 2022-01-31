#pragma once
#include <utility>
#include <vector>

#include "CBody.h"
#include "CSpring.h"
namespace Cinkes
{

	class CRigidBody : public CBody
	{
	public:
		CRigidBody(float a_Mass,
		           CVector3 a_CenterOfMass) : CBody(), m_Mass(a_Mass), m_InverseMass(1/a_Mass),
		                                      m_CenterOfMass(
			                                      std::move(a_CenterOfMass))
		{
			m_Moveable = true;
		}

		CRigidBody(const CTransform& a_Transform, const std::shared_ptr<CCollisionShape>& a_CollisionShape,
		            CScalar a_Mass,
		           const CVector3& a_CenterOfMass);


		CRigidBody(CBody&& a_Rhs, const std::vector<std::shared_ptr<CSpring>>& a_AttachedSprings,
		           float a_Mass, CVector3 a_CenterOfMass);

		CRigidBody(const CRigidBody& a_Rhs) : CBody(a_Rhs),m_Mass(a_Rhs.m_Mass), m_InverseMass(1/a_Rhs.m_Mass)
		{
		}

		CRigidBody(CRigidBody&& a_Rhs) noexcept;
		~CRigidBody() override = default;

		CRigidBody& operator=(CRigidBody&& a_Rhs) noexcept;  // NOLINT(bugprone-exception-escape)
		CRigidBody& operator=(const CRigidBody& a_Rhs);

		CScalar GetInverseMass() { return m_InverseMass; }
		CScalar GetInverseMass() const { return m_InverseMass; }
		CScalar GetMass() { return m_Mass; }
		CScalar GetMass() const { return m_Mass; }
		void SetMass(CScalar a_Rhs);
		CVector3 GetCenterOfMass() { return m_CenterOfMass; }
		CVector3 GetCenterOfMass() const { return m_CenterOfMass; }
		void SetCenterOfMass(const CVector3& a_Rhs) { m_CenterOfMass = a_Rhs; }

		CScalar GetAngularDamping() { return m_AngularDamping; }
		CScalar GetAngularDamping() const { return m_AngularDamping; }
		void SetAngularDamping(CScalar a_Amount) { m_AngularDamping = a_Amount; }

		void SetInertiaTensor(CMat3x3& a_Tensor) { m_InverseIntertiaTensor = a_Tensor.GetInverse(); }

		void* GetUserPointer1() { return m_UserPointer1; }
		void* GetUserPointer1() const { return m_UserPointer1; }
		void* GetUserPointer2() { return m_UserPointer1; }
		void* GetUserPointer2() const { return m_UserPointer1; }
		void SetUserPointer1(void* a_Pointer) { m_UserPointer1 = a_Pointer; }
		void SetUserPointer2(void* a_Pointer) { m_UserPointer2 = a_Pointer; }

		void AddForce(const CVector3& a_ForceToAdd) { m_Force += a_ForceToAdd; }
		void AddForceAtPoint(const CVector3& a_ForceToAdd, const CVector3& a_Point) { m_Force += a_ForceToAdd; }
		void AddTorque(const CVector3& a_TorqueToAdd) { m_Torque += a_TorqueToAdd; }
		CVector3& GetForce() { return m_Force; }
		CVector3& GetTorque() { return m_Torque; }
		void ClearForces() { m_Force = CVector3(0, 0, 0); m_Torque = CVector3(0, 0, 0); }


		void Integrate(CScalar a_T);

	private:
		CScalar m_Mass;
		CScalar m_InverseMass;
		CVector3 m_CenterOfMass;

		CMat3x3 m_InverseIntertiaTensor;

		CVector3 m_Velocity;
		CVector3 m_AngularVelocity;

		CScalar m_AngularDamping = 0.8f;
		CScalar m_LinearDamping = 0.8f;

		CVector3 m_LastFrameAcceleration;
		CVector3 m_Acceleration;
		CVector3 m_AngularAcceleration;

		CVector3 m_Torque;
		CVector3 m_Force;
		
		void* m_UserPointer1 = nullptr;
		void* m_UserPointer2 = nullptr;
	};
}

