#pragma once
#include "CVector3.h"
#include "CCollisionObject.h"
#include "CRigidBody.h"
namespace Cinkes
{
	class CBody;

	enum class ESPRING_TYPE
	{
		TYPE_BASIC = 0
	};

	struct CSpringData
	{
		
		CCollisionObject* m_Body[2]{ nullptr,nullptr };
		CVector3 m_Points[2];
		CScalar m_SpringConstant;
		CScalar m_RestLength;
		CScalar m_DampeningConstant;
	};

	class CSpring
	{
	public:
		CSpring(const CSpringData& a_Data)
		{
			m_Point[0] = a_Data.m_Points[0];

			if (a_Data.m_Body[0]->GetType() == EOBJECT_TYPE::TYPE_RIGID)
			{
				m_Body[0] = reinterpret_cast<CRigidBody*>(a_Data.m_Body[0]);
			}

			m_Point[1] = a_Data.m_Points[1];
			if (a_Data.m_Body[1] != nullptr && a_Data.m_Body[1]->GetType() == EOBJECT_TYPE::TYPE_RIGID)
			{
				m_Body[1] = reinterpret_cast<CRigidBody*>(a_Data.m_Body[1]);
			}

			m_SpringConstant = a_Data.m_SpringConstant;
			m_RestLength = a_Data.m_RestLength;
			m_Type = ESPRING_TYPE::TYPE_BASIC;
			m_DampeningConstant = a_Data.m_DampeningConstant;
		}
		ESPRING_TYPE GetType() const { return m_Type; }

		CRigidBody* GetBody1() { return m_Body[0]; }
		CRigidBody* GetBody1() const { return m_Body[0]; }
		bool SetBody1(CRigidBody* a_Body, const CVector3& a_ConnectionPointLocal) {
			if (a_Body != m_Body[0])
			{
				m_Point[1] = a_ConnectionPointLocal;
				m_Body[1] = a_Body;
				return true;
			}
			return false;
		}

		CRigidBody* GetBody2() { return m_Body[1]; }
		CRigidBody* GetBody2() const { return m_Body[1]; }
		bool SetBody2(CRigidBody* a_Body, const CVector3& a_ConnectionPointLocal)
		{
			if (a_Body != m_Body[0])
			{
				m_Point[1] = a_ConnectionPointLocal;
				m_Body[1] = a_Body;
				return true;
			}
			return false;
		}

		CVector3 GetPoint1() { return m_Point[0]; }
		CVector3 GetPoint1() const { return m_Point[0]; }
		void SetPoint1(const CVector3& a_Point) { m_Point[0] = a_Point; }

		CVector3 GetPoint2() { return m_Point[1]; }
		CVector3 GetPoint2() const { return m_Point[1]; }
		void SetPoint2(const CVector3& a_Point) { m_Point[1] = a_Point; }

		CScalar GetSpringConstant() { return m_SpringConstant; }
		CScalar GetSpringConstant() const { return m_SpringConstant; }
		void SetSpringConstant(CScalar a_Constant) { m_SpringConstant = a_Constant; }

		CScalar GetDampeningConstant() { return m_DampeningConstant; }
		CScalar GetDampeningConstant() const { return m_DampeningConstant; }
		void GetDampeningConstant(CScalar a_Constant) { m_DampeningConstant = a_Constant; }

		CScalar GetRestLength() { return m_RestLength; }
		CScalar GetRestLength() const { return m_RestLength; }
		void SetRestLength(CScalar a_Length) { m_RestLength = a_Length; }

		CScalar GetCubicStiffness() { return m_CubicStiffness; }
		CScalar GetCubicStiffness() const { return m_CubicStiffness; }
		void SetCubicStiffness(CScalar a_Constant) { m_CubicStiffness = a_Constant; }

	protected:

		CRigidBody* m_Body[2]{};
		CVector3 m_Point[2];
		CScalar m_SpringConstant;
		CScalar m_RestLength;
		CScalar m_DampeningConstant;
		CScalar m_CubicStiffness;
		ESPRING_TYPE m_Type;
	};
}
