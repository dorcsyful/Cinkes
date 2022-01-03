#pragma once
#include <vector>

#include "CConvexHull.h"
namespace Cinkes
{

	class CConcaveShape : CCollisionShape
	{
	public:
		//Subgroup: Constructors {
		CConcaveShape();
		CConcaveShape(std::vector<CVector3> a_Vertices);
		~CConcaveShape();
		CConcaveShape(const CConcaveShape& a_Rhs);
		CConcaveShape(CConcaveShape&& a_Rhs);
		//}

		//Subgroup: Operators {
		CConcaveShape& operator=(CConcaveShape&& a_Rhs);
		CConcaveShape& operator=(const CConcaveShape& a_Rhs);
		CVector3 operator[](int a_Rhs);
		CVector3 operator[](int a_Rhs) const;
		//}

		//Subgroup: Shaping {
		bool AddVertex(const CVector3& a_New);
		bool RemoveVertexByIndex(int a_Index);
		bool RemoveVertexByValue(const CVector3& a_Vertex);
		bool AddMultipleVertices(std::vector<CVector3> a_Array);
		std::vector<CVector3> SupportPointsForContact(const CVector3& a_Direction, const CTransform& a_Position) override;
		//}

	private:
		std::vector<CVector3> m_Vertices;
	};

}
