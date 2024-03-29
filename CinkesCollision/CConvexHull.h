#pragma once
#include <map>
#include <memory>
#include <vector>

#include "CCollisionShape.h"

namespace Cinkes
{
	class CConvexHull : CCollisionShape
	{
	public:
		//Subgroup: Constructors {
		CConvexHull() = default;
		~CConvexHull() override = default;
		CConvexHull(const CConvexHull& a_Rhs);
		CConvexHull(CConvexHull&& a_Rhs) noexcept;
		//}

		//Subgroup: Operators {
		CConvexHull& operator=(CConvexHull&& a_Rhs);
		CConvexHull& operator=(const CConvexHull& a_Rhs);
		//}

		//Subgroup: Other {
		CVector3 Support(const CVector3& a_V) override;
		bool AddSingleVertex(CVector3 a_Point, bool a_DelayBuild = false) {}
		bool AddVerticesAsArray(std::vector<CVector3>& a_Points, bool a_DelayBuild = false) {}
		void BuildHull() {}
		//}
		std::vector<CVector3> m_Vertices;
		std::vector<size_t> m_Faces;
		std::vector<CVector3> m_Normals;

	protected:

		ESHAPE_TYPE m_Type = ESHAPE_TYPE::SHAPE_CONVEX_HULL;

	};

}
