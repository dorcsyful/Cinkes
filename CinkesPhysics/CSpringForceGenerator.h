#pragma once
#include <iostream>
#include <ostream>

#include "CRigidBody.h"
#include "CForceGenerator.h"
#include "CSpring.h"
#include "CUtils.h"

namespace Cinkes
{

	class CSpringForceGenerator : public CForceGenerator
	{
	public:
		CSpringForceGenerator() { m_Type = EGENERATOR_TYPE::TYPE_SPRING_BASIC; }
		void UpdateForce(void* a_Body) override
		{
			m_Current = static_cast<CSpring*>(a_Body);
			
			if (m_Current->GetBody1() != nullptr)
			{
				m_Positions[0] = m_Current->GetBody1()->GetTransform().getOrigin();
				if (m_Current->GetBody1()->GetType() == EOBJECT_TYPE::TYPE_RIGID) { m_Velocities[0] = m_Current->GetBody1()->GetLinearVelocity(); }
			}
			else
			{
				m_Positions[0] = m_Current->GetPoint1();


			}
			if (m_Current->GetBody2() != nullptr)
			{
				m_Positions[1] = m_Current->GetBody2()->GetTransform().getOrigin();
				if (m_Current->GetBody2()->GetType() == EOBJECT_TYPE::TYPE_RIGID) { m_Velocities[1] = m_Current->GetBody2()->GetLinearVelocity(); }
			}
			else
			{
				m_Positions[1] = m_Current->GetPoint2();

			}


			if (m_Current->GetBody1() != nullptr) CalculateFirst();
			if (m_Current->GetBody2() != nullptr) CalculateSecond();
		}
		void CalculateFirst() const
		{
			// spring force
			CScalar dist = (m_Positions[0] - m_Positions[1]).Length();
			CScalar scalar = m_Current->GetBody1()->GetMass() * m_Current->GetSpringConstant() * (dist - m_Current->GetRestLength());
			CVector3 dir = CVector3::Normalize(m_Positions[1] - m_Positions[0]);

			// find speed of contraction/expansion for damping force
			CScalar s1 = CVector3::Dot(m_Velocities[0], dir);
			CScalar s2 = CVector3::Dot(m_Velocities[1], dir);
			CScalar dampingScalar = -m_Current->GetDampeningConstant() * (s1 + s2);
			CVector3 force;
			if (1.f == m_Current->GetBody1()->GetMass()) {
				force = dir * (scalar + dampingScalar);
			}
			else {
				force = dir * (-scalar + dampingScalar);
			}
			//std::cout << force.getY() << std::endl;
			m_Current->GetBody1()->AddForceAtPoint(force, m_Positions[0]);
			
		}
		void CalculateSecond() const
		{
			// spring force
			CScalar dist = (m_Positions[0] - m_Positions[1]).Length();
			CScalar scalar = m_Current->GetBody2()->GetMass() * m_Current->GetSpringConstant() * (dist - m_Current->GetRestLength());
			CVector3 dir = CVector3::Normalize(m_Positions[1] - m_Positions[0]);

			// find speed of contraction/expansion for damping force
			CScalar s1 = CVector3::Dot(m_Velocities[0], dir);
			CScalar s2 = CVector3::Dot(m_Velocities[1], dir);
			CScalar dampingScalar = -m_Current->GetDampeningConstant() * (s1 + s2);
			CVector3 force;
			if (1.f == m_Current->GetBody2()->GetMass()) {
				force = dir * (scalar + dampingScalar);
			}
			else {
				force = dir * (-scalar + dampingScalar);
			}
			//std::cout << force.getY() << std::endl;
			m_Current->GetBody2()->AddForceAtPoint(force, m_Positions[0]);
		}

		CSpring* m_Current = nullptr;
		CVector3 m_Positions[2];
		CVector3 m_Velocities[2];
	};

}
