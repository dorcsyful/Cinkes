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
				m_Positions[0] = m_Current->GetBody1()->GetTransform().getOrigin() + m_Current->GetPoint1();
				if (m_Current->GetBody1()->GetType() == EOBJECT_TYPE::TYPE_RIGID) { m_Velocities[0] = m_Current->GetBody1()->GetLinearVelocity(); }
			}
			else
			{
				m_Positions[0] = m_Current->GetPoint1();


			}
			if (m_Current->GetBody2() != nullptr)
			{
				m_Positions[1] = m_Current->GetBody2()->GetTransform().getOrigin() + m_Current->GetPoint2();
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
            CVector3 displacement = m_Positions[1] - m_Positions[0];
            CScalar distance = displacement.Length();
            displacement.Normalize();
            // Calculate the spring force based on Hooke's Law
            CVector3 springForce =  displacement * m_Current->GetSpringConstant() * (distance - m_Current->GetRestLength());

            // Calculate the damping force based on damping coefficient
            CVector3 dampingForce =  (m_Velocities[1] - m_Velocities[0]) * m_Current->GetDampeningConstant();

            // Return the total force applied at the attachment point
            
            m_Current->GetBody1()->AddForceAtPoint(springForce + dampingForce,m_Positions[0]);
        }

        void CalculateSecond() const
        {
            // spring force
            CScalar dist = (m_Positions[0] - m_Positions[1]).Length();
            CScalar scalar = m_Current->GetBody2()->GetMass() * m_Current->GetSpringConstant() * (dist - m_Current->GetRestLength());
            CVector3 dir = CVector3::Normalize(m_Positions[0] - m_Positions[1]);

            // find relative velocity for damping force
            CVector3 relVelocity = m_Velocities[1];
            if (m_Current->GetBody1() != nullptr)
            {
                relVelocity -= m_Current->GetBody1()->GetLinearVelocity();
            }

            CScalar dampingScalar = -m_Current->GetDampeningConstant() * CVector3::Dot(relVelocity, dir);
            CVector3 force;
            if (1.f == m_Current->GetBody2()->GetMass())
            {
                force = dir * (scalar + dampingScalar);
            }
            else
            {
                force = dir * (-scalar + dampingScalar);
            }

            m_Current->GetBody2()->AddForceAtPoint(force, m_Positions[1]);
        }

		CSpring* m_Current = nullptr;
		CVector3 m_Positions[2];
		CVector3 m_Velocities[2];
	};

}
