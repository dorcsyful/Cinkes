#include "CTestResolver.h"

#include <iostream>

#include "CRigidBody.h"

bool Cinkes::CTestResolver::Resolve(const std::vector<std::shared_ptr<CInternalContactInfo>>& a_Info, CScalar a_T) const
{
	for (const auto& info : a_Info)
	{
		CVector3 a_velocities;
		CVector3 b_velocities;

		for (auto& point : info->m_ContactPoints) {
			CVector3 actual = point - info->m_PenetrationDepth;
			CVector3 a_relative_position = actual - info->m_First->GetTransform().getOrigin();
			CVector3 b_relative_position = actual - info->m_Second->GetTransform().getOrigin();

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

			if (info->m_First->GetType() == EOBJECT_TYPE::TYPE_RIGID)
			{
				a = static_cast<CRigidBody*>(info->m_First.get());

				a_angular_velocity/* = CVector3::Cross(a->GetAngularVelocity(), a_relative_position)*/;
				a_full_velocity = a->GetLinearVelocity() + a_angular_velocity;

				a_inverse_mass = a->GetInverseMass();
				a->SetInverseInertiaTensorWorld();
				a_inverse_inertia_tensor = a->GetInverseInertiaTensorWorld();
			}

			if (info->m_Second->GetType() == EOBJECT_TYPE::TYPE_RIGID)
			{
				b = static_cast<CRigidBody*>(info->m_Second.get());
				b_inverse_mass = b->GetInverseMass();
				b_angular_velocity/* = CVector3::Cross(b->GetAngularVelocity(), b_relative_position)*/;
				b_full_velocity = b->GetLinearVelocity() + b_angular_velocity;
			}

			if (a)
			{

			}
			if (b)
			{
				CVector3 contact_velocity = b_full_velocity - a_full_velocity;
				CScalar impulse_force = ((1.f + 0.1f) * -1) * (CVector3::Dot(contact_velocity, info->m_Normal));
				CVector3 a_cross_point_normal = a_relative_position.Cross(info->m_Normal);
				a_cross_point_normal = (a_inverse_inertia_tensor * (a_cross_point_normal)).Cross(a_cross_point_normal);
				CVector3 b_cross_point_normal = b_relative_position.Cross(info->m_Normal);
				b_cross_point_normal = (b_inverse_inertia_tensor * (b_cross_point_normal)).Cross(b_cross_point_normal);
				CScalar k = a_inverse_mass + b_inverse_mass + (a_cross_point_normal + b_cross_point_normal).Dot(info->m_Normal);
				CScalar normal_impulse = impulse_force / k;

				//Linear
				CVector3 p = (info->m_Normal * normal_impulse) * a_inverse_mass;
				b->SetLinearVelocity(a->GetLinearVelocity() - p);

				//Angular
				CVector3 b_position_cross_normal = (b_relative_position.Cross((info->m_Normal * normal_impulse)));
				b_position_cross_normal = a_inverse_inertia_tensor * b_position_cross_normal;
				b->SetAngularVelocity(b->GetAngularVelocity() - b_position_cross_normal);
			}
		}
		if (a_velocities != CVector3(0,0,0)) {
			CRigidBody* first = static_cast<CRigidBody*>(info->m_First.get());
			CVector3 current_velocity = first->GetLinearVelocity();
			first->SetLinearVelocity((current_velocity + a_velocities) * a_T);
		}
	}
    return false;
}

void Cinkes::CTestResolver::SetUp(const std::vector<std::shared_ptr<Cinkes::CInternalContactInfo>>& a_Info, CScalar a_T)
{
	for (auto& info : a_Info) {
		for (auto& point : info->m_ContactPoints) {

		}
	}
}
