#pragma once
#include "CForceGenerator.h"
#include "CRigidBody.h"
#include "CVector3.h"
namespace Cinkes
{

	class CGravityGenerator : public CForceGenerator
	{
	public:
		CGravityGenerator() { m_Type = EGENERATOR_TYPE::TYPE_GRAVITY; }
		void UpdateForce(CBody* a_Body, float a_T) override {
			if (m_Enabled)
			{
				a_Body->AddForce(m_Gravity * static_cast<CRigidBody*>(a_Body)->GetMass());
			}
		}
		void SetGravity(const CVector3& a_New) { m_Gravity = a_New; }
		CVector3 GetGravity() const { return m_Gravity; }
		void DisableGravity(bool a_New) { m_Enabled = a_New; }
		bool IsEnabled() const { return m_Enabled; }
	private:
		CVector3 m_Gravity = CVector3(0,0,0);
		bool m_Enabled = true;

	};
}
