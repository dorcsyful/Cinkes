#pragma once
#include "CVector3.h"

namespace Cinkes
{
	class CBody;

	enum class ESPRING_TYPE
	{
		TYPE_BASIC = 0
	};

	class CSpring
	{
	public:
		CSpring(CRigidBody* a_Body1, const CVector3& a_Point1,CRigidBody* a_Body2, const CVector3& a_Point2, CScalar a_SpringConstant,CScalar a_RestLength)
		{
			m_Body1 = a_Body1;
			m_LocalConnectionPoint1 = a_Point1;
			m_Body2 = a_Body2;
			m_LocalConnectionPoint2 = a_Point2;
			m_SpringConstant = a_SpringConstant;
			m_RestLength = a_RestLength;
			m_Type = ESPRING_TYPE::TYPE_BASIC;
		}
		ESPRING_TYPE GetType() const { return m_Type; }

		CRigidBody* GetBody1() { return m_Body1; }
		CRigidBody* GetBody1() const { return m_Body1; }
		bool SetBody1(CRigidBody* a_Body) { if (a_Body != m_Body2) { m_Body1 = a_Body; return true; } return false; }

		CRigidBody* GetBody2() { return m_Body2; }
		CRigidBody* GetBody2() const { return m_Body2; }
		bool SetBody2(CRigidBody* a_Body) { if (a_Body != m_Body1) { m_Body2 = a_Body; return true; } return false; }

		CVector3 GetLocalConnectionPoint1() { return m_LocalConnectionPoint1; }
		CVector3 GetLocalConnectionPoint1() const { return m_LocalConnectionPoint1; }
		void SetLocalConnectionPoint1(const CVector3& a_Point) { m_LocalConnectionPoint1 = a_Point; }

		CVector3 GetLocalConnectionPoint2() { return m_LocalConnectionPoint2; }
		CVector3 GetLocalConnectionPoint2() const { return m_LocalConnectionPoint2; }
		void SetLocalConnectionPoint2(const CVector3& a_Point) { m_LocalConnectionPoint2 = a_Point; }

		CScalar GetSpringConstant() { return m_SpringConstant; }
		CScalar GetSpringConstant() const { return m_SpringConstant; }
		void SetSpringConstant(CScalar a_Constant) { m_SpringConstant = a_Constant; }

		CScalar GetRestLength() { return m_RestLength; }
		CScalar GetRestLength() const { return m_RestLength; }
		void SetRestLength(CScalar a_Length) { m_RestLength = a_Length; }

	protected:
		CVector3 m_LocalConnectionPoint1;
		CVector3 m_LocalConnectionPoint2;
		CRigidBody* m_Body1;
		CRigidBody* m_Body2;
		CScalar m_SpringConstant;
		CScalar m_RestLength;

		ESPRING_TYPE m_Type;
	};
}
