#include "CTestResolver.h"

#include <iostream>

#include "CRigidBody.h"

bool Cinkes::CTestResolver::Resolve(const std::vector<std::shared_ptr<CContactInfo>>& a_Info, CScalar a_T) const
{
	for (const auto& element : a_Info)
	{
		CRigidBody* a = nullptr;
		CVector3 a_velocity;
		CScalar a_inverse_mass = 0;
		CRigidBody* b = nullptr;
		CVector3 b_velocity;
		CScalar b_inverse_mass = 0;
		if(element->m_First->GetType() == EOBJECT_TYPE::TYPE_RIGID)
		{
			a = static_cast<CRigidBody*>(element->m_First.get());
			a_velocity = a->GetLinearVelocity();
			a_inverse_mass = a->GetInverseMass();
		}

		if(element->m_Second->GetType() == EOBJECT_TYPE::TYPE_RIGID)
		{
			b = static_cast<CRigidBody*>(element->m_Second.get());
			b_velocity = b->GetLinearVelocity();
			b_inverse_mass = b->GetInverseMass();
		}

		if(a)
		{
			CScalar top = ((a_velocity - b_velocity) * -(1 + 0.f)).Dot(element->m_Normal);
			CScalar middle = top / element->m_Normal.Dot(element->m_Normal *(a_inverse_mass + b_inverse_mass));
			CScalar bottom = middle / a->GetMass();
			CVector3 temp = element->m_Normal * bottom;
			a_velocity = a_velocity + temp;
			std::cout << "Velocity after collision resolution: " << a_velocity.getY() << std::endl;
			//a->GetTransform().setOrigin(a->GetTransform().getOrigin() + a_velocity * a_T);
			a->SetLinearVelocity(a_velocity);

		}
		if (b)
		{
			CScalar top = -(1 + 1) * (a_velocity - b_velocity).Dot(element->m_Normal);
			CScalar middle = top / (a_inverse_mass + b_inverse_mass);
			CScalar bottom = middle / b->GetMass();
			b_velocity += element->m_Normal * -1 * bottom;
			b->GetTransform().setOrigin(b->GetTransform().getOrigin() + b_velocity * a_T);
			b->SetLinearVelocity(b_velocity);

		}
	}
    return false;
}
