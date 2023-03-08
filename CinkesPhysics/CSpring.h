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
	};

	class CSpring
	{
	public:
		CSpring(const CSpringData& a_Data)
		{
			if(a_Data.m_Body[0] == nullptr) { m_Point[0] = a_Data.m_Points[0]; }
			else if (a_Data.m_Body[0]->GetType() == EOBJECT_TYPE::TYPE_RIGID)
			{
				m_Body[0] = reinterpret_cast<CRigidBody*>(a_Data.m_Body[0]);
			}
			else{ m_Point[0] = a_Data.m_Body[0]->GetTransform().getOrigin(); }

			if (a_Data.m_Body[1] == nullptr) { m_Point[1] = a_Data.m_Points[1]; }
			else if (a_Data.m_Body[1]->GetType() == EOBJECT_TYPE::TYPE_RIGID)
			{
				m_Body[1] = reinterpret_cast<CRigidBody*>(a_Data.m_Body[1]);
			}
			else { m_Point[1] = a_Data.m_Body[1]->GetTransform().getOrigin(); }

			m_SpringConstant = a_Data.m_SpringConstant;
			m_RestLength = a_Data.m_RestLength;
			m_Type = ESPRING_TYPE::TYPE_BASIC;
		}
		ESPRING_TYPE GetType() const { return m_Type; }

		CRigidBody* GetBody1() { return m_Body[0]; }
		CRigidBody* GetBody1() const { return m_Body[0]; }
		bool SetBody1(CRigidBody* a_Body) { if (a_Body != m_Body[1]) { m_Body[0] = a_Body; return true; } return false; }

		CRigidBody* GetBody2() { return m_Body[1]; }
		CRigidBody* GetBody2() const { return m_Body[1]; }
		bool SetBody2(CRigidBody* a_Body) { if (a_Body != m_Body[0]) { m_Body[1] = a_Body; return true; } return false; }

		CVector3 GetLocalConnectionPoint1() { return m_Point[0]; }
		CVector3 GetLocalConnectionPoint1() const { return m_Point[0]; }
		void SetLocalConnectionPoint1(const CVector3& a_Point) { m_Point[0] = a_Point; }

		CVector3 GetLocalConnectionPoint2() { return m_Point[1]; }
		CVector3 GetLocalConnectionPoint2() const { return m_Point[1]; }
		void SetLocalConnectionPoint2(const CVector3& a_Point) { m_Point[1] = a_Point; }

		CScalar GetSpringConstant() { return m_SpringConstant; }
		CScalar GetSpringConstant() const { return m_SpringConstant; }
		void SetSpringConstant(CScalar a_Constant) { m_SpringConstant = a_Constant; }

		CScalar GetRestLength() { return m_RestLength; }
		CScalar GetRestLength() const { return m_RestLength; }
		void SetRestLength(CScalar a_Length) { m_RestLength = a_Length; }

	protected:

		CRigidBody* m_Body[2]{};
		CVector3 m_Point[2];
		CScalar m_SpringConstant;
		CScalar m_RestLength;

		ESPRING_TYPE m_Type;
	};
}
