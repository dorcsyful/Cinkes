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
		CRigidBody(std::vector<std::shared_ptr<CSpring>> a_AttachedSprings, float a_Mass,
		           CVector3 a_CenterOfMass) : CBody(), m_AttachedSprings(std::move(a_AttachedSprings)), m_Mass(a_Mass),
		                                      m_CenterOfMass(
			                                      std::move(a_CenterOfMass))
		{
			m_Moveable = true;
		}

		CRigidBody(const CTransform& a_Transform, const std::shared_ptr<CBody>& a_CollisionShape,
		           const std::vector<std::shared_ptr<CSpring>>& a_AttachedSprings, CScalar a_Mass,
		           const CVector3& a_CenterOfMass);


		CRigidBody(CBody&& a_Rhs, const std::vector<std::shared_ptr<CSpring>>& a_AttachedSprings,
		           float a_Mass, CVector3 a_CenterOfMass);

		CRigidBody(const CRigidBody& a_Rhs) : CBody(a_Rhs), m_Mass(1)
		{
		}

		CRigidBody(CRigidBody&& a_Rhs) noexcept;
		~CRigidBody() override = default;

		CRigidBody& operator=(CRigidBody&& a_Rhs) noexcept;  // NOLINT(bugprone-exception-escape)
		CRigidBody& operator=(const CRigidBody& a_Rhs);

		std::vector < std::shared_ptr<CSpring>> GetAllSprings();
		std::vector < std::shared_ptr<CSpring>> GetSpringsByType(ESPRING_TYPE a_Type);
		CScalar GetMass();
		CScalar GetMass() const;
		void SetMass(CScalar a_Rhs);
		CVector3 GetCenterOfMass();
		CVector3 GetCenterOfMass() const;
		void SetCenterOfMass(const CVector3& a_Rhs);


	private:
		std::vector < std::shared_ptr<CSpring>> m_AttachedSprings;
		CScalar m_Mass;
		CVector3 m_CenterOfMass;
	};
}

