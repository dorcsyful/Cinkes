#pragma once
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
			
			if (m_Current->GetBody1() != nullptr) { m_Positions[0] = m_Current->GetBody1()->GetTransform().getOrigin(); }
			else { m_Positions[0] = m_Current->GetLocalConnectionPoint1(); }
			if (m_Current->GetBody2() != nullptr) { m_Positions[1] = m_Current->GetBody2()->GetTransform().getOrigin(); }
			else { m_Positions[1] = m_Current->GetLocalConnectionPoint2(); }

			CalculateFirst();
			CalculateSecond();
		}
		void CalculateFirst() const
		{
			// Calculate the vector of the spring.
			CVector3 force = m_Positions[0] - m_Positions[1];
			// Calculate the magnitude of the force.
			CScalar length = force.Length();
			length = CUtils::Abs(length - m_Current->GetRestLength());
			length *= m_Current->GetSpringConstant();
			// Calculate the final force and apply it.
			force.Normalize();
			force *= -length;
			if(m_Current->GetBody1() != nullptr)
			{
				m_Current->GetBody1()->AddForceAtPoint(force, m_Positions[0]);
			}
			
		}
		void CalculateSecond() const
		{
			CVector3 force = m_Positions[0] - m_Positions[1];
			// Calculate the magnitude of the force.
			CScalar length = force.Length();
			length = CUtils::Abs(length - m_Current->GetRestLength());
			length *= m_Current->GetSpringConstant();
			// Calculate the final force and apply it.
			force.Normalize();
			force *= -length;
			if(m_Current->GetBody2() != nullptr) m_Current->GetBody2()->AddForceAtPoint(force, m_Positions[1]);
		}

		CSpring* m_Current = nullptr;
		CVector3 m_Positions[2];
	};

}
