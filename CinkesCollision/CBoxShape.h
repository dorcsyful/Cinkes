#pragma once
#include "CCollisionShape.h"
#include "CMat3x3.h"
#include "../CinkesMath/CScalar.h"
#include "../CinkesMath/CVector3.h"
#include "CLine.h"
#include "CConvexHull.h"

namespace Cinkes
{

	class CBoxShape : public CConvexHull
	{
	public:
		//Subgroup: Constructors {
		CBoxShape() { m_Vertices.resize(8); m_Type = ESHAPE_TYPE::SHAPE_BOX; }
		CBoxShape(CVector3 a_Dimensions) {
			m_Dimensions = a_Dimensions;
			SetVertices();
		}
		CBoxShape(const CScalar a_X, const CScalar a_Y, const CScalar a_Z) { 
			m_Dimensions = CVector3(a_X, a_Y, a_Z);
			SetVertices();
		}
		~CBoxShape() override = default;
		CBoxShape(const CBoxShape& a_Rhs) = default;
		CBoxShape(CBoxShape&& a_Rhs) noexcept : m_Dimensions(a_Rhs.m_Dimensions) {
			SetVertices();
		}
		//}

		//Subgroup: Operators {
		CBoxShape& operator=(CBoxShape&& a_Rhs) noexcept { 
			m_Dimensions = a_Rhs.m_Dimensions; 
			SetVertices(); 
			return *this; 
		}
		CBoxShape& operator=(const CBoxShape& a_Rhs) noexcept { 
			m_Dimensions = a_Rhs.m_Dimensions; 
			SetVertices(); 
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
			m_Dimensions = a_Dimensions; 
			SetVertices(); };
		void SetDimensions(const CScalar& a_X, const CScalar& a_Y, const CScalar& a_Z) { 
			m_Dimensions = CVector3(a_X, a_Y, a_Z); 
			SetVertices(); };

		CVector3 Support(const CVector3& a_V) override;
		CLine GetEdge(int a_Axis, const CVector3& a_Direction);
		void CreateAABB(CVector3& a_Min, CVector3& a_Max) override;
		CMat3x3 CalculateInertiaTensor(CScalar a_Mass) override;
		void SetVertices() {
			m_Vertices.clear();
			m_Vertices[0] = CPoint(-m_Dimensions[0], -m_Dimensions[1], -m_Dimensions[2]);
			m_Vertices[1] = CPoint(-m_Dimensions[0], -m_Dimensions[1], m_Dimensions[2]);
			m_Vertices[2] = CPoint(-m_Dimensions[0], m_Dimensions[1], m_Dimensions[2]);
			m_Vertices[3] = CPoint(-m_Dimensions[0], m_Dimensions[1], -m_Dimensions[2]);
			m_Vertices[4] = CPoint(m_Dimensions[0], -m_Dimensions[1], -m_Dimensions[2]);
			m_Vertices[5] = CPoint(m_Dimensions[0], -m_Dimensions[1], m_Dimensions[2]);
			m_Vertices[6] = CPoint(m_Dimensions[0], m_Dimensions[1], m_Dimensions[2]);
			m_Vertices[7] = CPoint(m_Dimensions[0], m_Dimensions[1], -m_Dimensions[2]);
		}

	private:
		CVector3 m_Dimensions;
	};
}
