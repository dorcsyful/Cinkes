#pragma once
#include "CCollisionShape.h"
#include "CMat3x3.h"
#include "../CinkesMath/CScalar.h"
#include "../CinkesMath/CVector3.h"
#include "CLine.h"
#include "CConvexHull.h"
#include <cassert>

namespace Cinkes
{

	class CBoxShape : public CCollisionShape
	{
	public:
		//Subgroup: Constructors {
		CBoxShape() { m_Type = ESHAPE_TYPE::SHAPE_BOX; }
		CBoxShape(CVector3 a_Dimensions) {
			m_Type = ESHAPE_TYPE::SHAPE_BOX;
			SetDimensions(a_Dimensions);
		}
		CBoxShape(const CScalar a_X, const CScalar a_Y, const CScalar a_Z) { 
			m_Type = ESHAPE_TYPE::SHAPE_BOX;
			SetDimensions(a_X,a_Y,a_Z);
		}
		~CBoxShape() override = default;
		CBoxShape(const CBoxShape& a_Rhs) = default;
		CBoxShape(CBoxShape&& a_Rhs) noexcept : m_Dimensions(a_Rhs.m_Dimensions) {}
		//}

		//Subgroup: Operators {
		CBoxShape& operator=(CBoxShape&& a_Rhs) noexcept { 
			m_Dimensions = a_Rhs.m_Dimensions; 
			return *this; 
		}
		CBoxShape& operator=(const CBoxShape& a_Rhs) noexcept { 
			m_Dimensions = a_Rhs.m_Dimensions; 
			return *this; 
		}
		//}

		CVector3 GetDimensions() const { return m_Dimensions; };
		void GetDimensions(CScalar& a_X, CScalar& a_Y, CScalar& a_Z) { 
			a_X = m_Dimensions[0]; 
			a_Y = m_Dimensions[1]; 
			a_Z = m_Dimensions[2]; 
		};

		void SetDimensions(const CVector3& a_Dimensions) { 
			SetDimensions(a_Dimensions[0], a_Dimensions[1], a_Dimensions[2]);
		};
		void SetDimensions(const CScalar& a_X, const CScalar& a_Y, const CScalar& a_Z) { 
			assert(a_X != 0 && a_Y != 0 && a_Z != 0);
			m_Dimensions = CVector3(a_X, a_Y, a_Z); 
			 
		};

		CVector3 Support(const CVector3& a_V);
		void CreateAABB(const CMat3x3& a_Rotation, CVector3& a_Min, CVector3& a_Max) override;
		CMat3x3 CalculateInertiaTensor(CScalar a_Mass) override;
	private:
		CVector3 m_Dimensions;
	};
}
