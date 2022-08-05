#pragma once
#include <map>
#include <memory>
#include <vector>

#include "CCollisionShape.h"
#include "CPoint.h"

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
		bool AddSingleVertex(CPoint a_Point, bool a_DelayBuild = false) {}
		bool AddVerticesAsArray(std::vector<CPoint>& a_Points, bool a_DelayBuild = false) {}
		void BuildHull() {}
		//}
	protected:
		std::vector<CPoint> m_Vertices;
		ESHAPE_TYPE m_Type = ESHAPE_TYPE::SHAPE_CONVEX_HULL;

	};

}
