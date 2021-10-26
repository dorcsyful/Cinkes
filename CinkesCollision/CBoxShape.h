#pragma once
#include "CCollisionShape.h"
#include "../CinkesMath/CScalar.h"
#include "../CinkesMath/CVector3.h"

namespace Cinkes
{

	class CBoxShape : CCollisionShape
	{
	public:
		//Subgroup: Constructors {
		CBoxShape() = default;
		CBoxShape(const CVector3& a_Dimensions) { m_Dimensions = a_Dimensions; };
		CBoxShape(const CScalar a_X, const CScalar a_Y, const CScalar a_Z) { m_Dimensions = CVector3(a_X, a_Y, a_Z); };
		~CBoxShape() override = default;
		CBoxShape(const CBoxShape& a_Rhs) { m_Dimensions = a_Rhs.m_Dimensions; };
		CBoxShape(CBoxShape&& a_Rhs) noexcept { m_Dimensions = a_Rhs.m_Dimensions; };
		//}

		//Subgroup: Operators {
		CBoxShape& operator=(CBoxShape&& a_Rhs) noexcept { m_Dimensions = a_Rhs.m_Dimensions; return *this; };
		CBoxShape& operator=(const CBoxShape& a_Rhs) { m_Dimensions = a_Rhs.m_Dimensions; return *this; };
		//}

		CVector3 GetDimensions() const { return m_Dimensions; };
		void GetDimensions(CScalar& a_X, CScalar& a_Y, CScalar& a_Z) { a_X = m_Dimensions[0]; a_Y = m_Dimensions[1]; a_Z = m_Dimensions[2]; };

		void SetDimensions(const CVector3& a_Dimensions) { m_Dimensions = a_Dimensions; };
		void SetDimensions(const CScalar& a_X, const CScalar& a_Y, const CScalar& a_Z) { m_Dimensions = CVector3(a_X, a_Y, a_Z); };

		CVector3 Support(const CVector3& a_V) override;
		void CreateAABB(CVector3& a_Min, CVector3& a_Max) { a_Min = m_Dimensions * (-1); a_Max = m_Dimensions; };

	private:
		CVector3 m_Dimensions;
		ESHAPE_TYPE m_Type = ESHAPE_TYPE::SHAPE_BOX;
	};
}
