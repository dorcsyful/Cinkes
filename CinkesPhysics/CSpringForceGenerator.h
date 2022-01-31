#pragma once
#include "CRigidBody.h"
#include "CForceGenerator.h"
#include "CSpring.h"
#include "CUtils.h"

namespace Cinkes
{

	class CSpringForceGenerator : public CForceGenerator
	{
		CSpringForceGenerator() { m_Type = EGENERATOR_TYPE::TYPE_SPRING_BASIC; }
		void UpdateForce(void* a_Body) override
		{
			current = static_cast<CSpring*>(a_Body);
			CalculateFirst();
			CalculateSecond();
		}
		void CalculateFirst() const
		{

			// Calculate the two ends in world space.
			CVector3 End1 = current->GetBody1()->GetTransform() * current->GetLocalConnectionPoint1();
			CVector3 End2 = current->GetBody2()->GetTransform() * current->GetLocalConnectionPoint2();
			// Calculate the vector of the spring.
			CVector3 force = End1 - End2;
			// Calculate the magnitude of the force.
			CScalar length = force.Length();
			length = CUtils::Abs(length - current->GetRestLength());
			length *= current->GetSpringConstant();
			// Calculate the final force and apply it.
			force.Normalize();
			force *= -length;
			current->GetBody1()->AddForceAtPoint(force, End1);
		}
		void CalculateSecond() const
		{

			// Calculate the two ends in world space.
			CVector3 End1 = current->GetBody2()->GetTransform() * current->GetLocalConnectionPoint2();
			CVector3 End2 = current->GetBody1()->GetTransform() * current->GetLocalConnectionPoint1();
			// Calculate the vector of the spring.
			CVector3 force = End1 - End2;
			// Calculate the magnitude of the force.
			CScalar length = force.Length();
			length = CUtils::Abs(length - current->GetRestLength());
			length *= current->GetSpringConstant();
			// Calculate the final force and apply it.
			force.Normalize();
			force *= -length;
			current->GetBody2()->AddForceAtPoint(force, End1);
		}

		CSpring* current = nullptr;
	};

}
