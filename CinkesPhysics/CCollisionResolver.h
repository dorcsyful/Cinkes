#pragma once
#include <memory>
#include <vector>

#include "CMat3x3.h"

namespace Cinkes
{
	class CRigidBody;
	class CCollisionObject;
	struct CContactInfo;

	class CCollisionResolver
	{
	public:
		CCollisionResolver() = default;
		~CCollisionResolver() = default;
		CCollisionResolver(CCollisionResolver&& a_Rhs) = delete;
		CCollisionResolver(const CCollisionResolver& a_Rhs) = delete;

		CCollisionResolver& operator=(CCollisionResolver&& a_Rhs) noexcept = delete;
		CCollisionResolver& operator=(const CCollisionResolver& a_Rhs) = delete;

		bool Resolve(const std::vector<CContactInfo*>& a_Info, CScalar a_T);
		CMat3x3 CalculateContactBasis(const CContactInfo* a_Info);
		void StepOne(CContactInfo* a_Info, CScalar a_T);
		void StepTwo(std::vector<CContactInfo*> a_Info, CScalar a_T);
		void StepThree(std::vector<CContactInfo*> a_Info, CScalar a_T);

		CVector3 ConvertToRelative(CCollisionObject* a_Object, const CVector3& a_Position);
		CVector3 ConvertToWorld(CCollisionObject* a_Object, const CVector3& a_Position);
		void MakeOrthoBasis(CVector3* a_X, CVector3* a_Y, CVector3* a_Z);
		void CalculateDeltaVelocity(CScalar a_T);
		CVector3 CalculateLocalVelocity(unsigned a_Index, CScalar a_T);
		bool SetRigidBodies();
		void ApplyPositionChange(CVector3 a_LinearChange[2], CVector3 a_AngularChange[2], CScalar a_Penetration);
		void ApplyVelocityChange(CContactInfo* a_Info, CVector3 a_VelocityChange[2], CVector3 a_RotationChange[2]);
		CVector3 FrictionlessImpulse(CMat3x3 a_Tensor[2], CScalar a_DesiredVelocity);
		CVector3 FrictionImpulse(CMat3x3 a_Tensor[2], CScalar a_DesiredVelocity, CScalar a_Friction);

	private:
		//Temporary values so we can easily handle them across multiple functions
		CMat3x3 m_ContactToWorld;
		CVector3 m_RelativeContactPosition[2];
		CVector3 m_ContactVelocity;
		CRigidBody* m_Body[2];
		CVector3* m_Normal;
		CContactInfo* m_Info;
		CScalar m_DeltaVelocity;
	};
}

