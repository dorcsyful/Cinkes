#pragma once
#include <memory>
#include <vector>

#include "CMat3x3.h"

namespace Cinkes
{
	class CRigidBody;
	class CCollisionObject;
	struct CInternalContactInfo;

	class CCollisionResolver
	{
	public:
		CCollisionResolver() = default;
		~CCollisionResolver() = default;
		CCollisionResolver(CCollisionResolver&& a_Rhs) = delete;
		CCollisionResolver(const CCollisionResolver& a_Rhs) = delete;

		CCollisionResolver& operator=(CCollisionResolver&& a_Rhs) noexcept = delete;
		CCollisionResolver& operator=(const CCollisionResolver& a_Rhs) = delete;

		bool Resolve(std::vector<std::shared_ptr<CInternalContactInfo>>& a_Info, CScalar a_T) const;
		CMat3x3 CalculateContactBasis(const CInternalContactInfo* a_Info) const;
		void StepOne(const std::vector<std::shared_ptr<CInternalContactInfo>>& a_Info, CScalar a_T) const;
		void StepTwo(const std::vector<std::shared_ptr<CInternalContactInfo>>& a_Info, CScalar a_T) const;
		void StepThree(std::vector<std::shared_ptr<CInternalContactInfo>>& a_Info, CScalar a_T) const;

		CVector3 ConvertToRelative(CCollisionObject* a_Object, const CVector3& a_Position) const;
		CVector3 ConvertToWorld(CCollisionObject* a_Object, const CVector3& a_Position) const;
		void CalculateDeltaVelocity(CScalar a_T, CInternalContactInfo* a_Info) const;
		CVector3 CalculateLocalVelocity(unsigned a_Index, CScalar a_T, CInternalContactInfo* a_Info) const;
		void ApplyPositionChange(CVector3 a_LinearChange[2], CVector3 a_AngularChange[2], CScalar a_Penetration, CInternalContactInfo* a_Info) const;
		void ApplyVelocityChange(CInternalContactInfo* a_Info, CVector3 a_VelocityChange[2], CVector3 a_RotationChange[2]) const;
		CVector3 FrictionlessImpulse(CMat3x3 a_Tensor[2], CScalar a_DesiredVelocity, CInternalContactInfo* a_Info) const;
		CVector3 FrictionImpulse(CMat3x3 a_Tensor[2], CScalar a_DesiredVelocity, CScalar a_Friction, CInternalContactInfo* a_Info) const;

	private:
		//CInternalContactInfo* m_Info;
		//CVector3 m_Normal;
		//CVector3 m_ContactVelocity;
		//CMat3x3 m_ContactToWorld;
		//CRigidBody* m_Body[2];
		//CVector3 m_RelativeContactPosition[2];
	};
}

