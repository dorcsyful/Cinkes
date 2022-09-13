#include "CTestResolver.h"

#include <iostream>

#include "CRigidBody.h"

bool Cinkes::CTestResolver::Resolve(const std::vector<std::shared_ptr<CContactInfo>>& a_Info, CScalar a_T) const
{
	for (const auto& element : a_Info)
	{

		CVector3 a_relative_position;
		CVector3 b_relative_position;

		CVector3 a_angular_velocity = CVector3(0, 0, 0);
		CVector3 b_angular_velocity = CVector3(0, 0, 0);

		CRigidBody* a = nullptr;
		CRigidBody* b = nullptr;

		CVector3 a_full_velocity;
		CVector3 b_full_velocity;

		CScalar a_inverse_mass = 0;
		CScalar b_inverse_mass = 0;
		CScalar total_mass = 0;

		CMat3x3 a_inverse_inertia_tensor = CMat3x3(0, 0, 0, 0, 0, 0, 0, 0, 0);
		CMat3x3 b_inverse_inertia_tensor = CMat3x3(0, 0, 0, 0, 0, 0, 0, 0, 0);

		if(element->m_First->GetType() == EOBJECT_TYPE::TYPE_RIGID)
		{
			a = static_cast<CRigidBody*>(element->m_First.get());

			a_angular_velocity = CVector3::Cross(a->GetAngularVelocity(), a_relative_position);
			a_full_velocity = a->GetLinearVelocity() + a_angular_velocity;

			a_inverse_mass = a->GetInverseMass();
			a->SetInverseInertiaTensor();
			a->SetInverseInertiaTensorWorld();
			a_inverse_inertia_tensor = a->GetInverseInertiaTensorWorld();
		}

		if(element->m_Second->GetType() == EOBJECT_TYPE::TYPE_RIGID)
		{
			b = static_cast<CRigidBody*>(element->m_Second.get());
			b_inverse_mass = b->GetInverseMass();
			b_angular_velocity = CVector3::Cross(b->GetAngularVelocity(), b_relative_position);
			b_full_velocity = b->GetLinearVelocity() + b_angular_velocity;


		}

		if(a)
		{
			CVector3 contact_velocity = a_full_velocity - b_full_velocity;
			CScalar impulse_force = CVector3::Dot(contact_velocity, element->m_Normal);
			CVector3 firstcross = CVector3::Cross(a_relative_position, element->m_Normal);
			firstcross = a_inverse_inertia_tensor * firstcross;
			CVector3 a_inertia = CVector3::Cross(firstcross , a_relative_position);
			CVector3 b_inertia = CVector3::Cross(b_inverse_inertia_tensor * CVector3::Cross(b_relative_position, element->m_Normal), b_relative_position);
			CScalar angular_effect = CVector3::Dot(a_inertia + b_inertia, element->m_Normal);
			CScalar j = (-(1.f + 0.0f) * impulse_force) / (a_inverse_mass + b_inverse_mass + angular_effect);
			CVector3 full_impulse = element->m_Normal * j;
			a->SetLinearVelocity(a->GetLinearVelocity() + (full_impulse * a_inverse_mass));
			CVector3 angular_impulse = a_inverse_inertia_tensor * CVector3::Cross(a_relative_position, full_impulse * -1);
			a->SetAngularVelocity(a->GetAngularVelocity() + angular_impulse);

		}
		if (b)
		{
			CVector3 contact_velocity = b_full_velocity - a_full_velocity;
			CScalar impulse_force = CVector3::Dot(contact_velocity, element->m_Normal);
			CVector3 a_inertia = CVector3::Cross(a_inverse_inertia_tensor * CVector3::Cross(a_relative_position, element->m_Normal), a_relative_position);
			CVector3 b_inertia = CVector3::Cross(b_inverse_inertia_tensor * CVector3::Cross(b_relative_position, element->m_Normal), b_relative_position);
			CScalar angular_effect = CVector3::Dot(a_inertia + b_inertia, element->m_Normal);
			CScalar j = (-(1.f + 0.33f) * impulse_force) / (a_inverse_mass + b_inverse_mass + angular_effect);
			CVector3 full_impulse = element->m_Normal * j;
			b->SetLinearVelocity(b->GetLinearVelocity() + (full_impulse * b_inverse_mass));
			CVector3 angular_impulse = b_inverse_inertia_tensor * CVector3::Cross(b_relative_position, full_impulse);
			b->SetAngularVelocity(b->GetAngularVelocity() + angular_impulse);

		}
	}
    return false;
}
