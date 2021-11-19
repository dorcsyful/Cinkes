#pragma once
#include <map>
#include <memory>
#include <vector>

#include "CCollisionShape.h"
#include "CVertex.h"

namespace Cinkes
{
	class CConvexHull : CCollisionShape
	{
	public:
		//Subgroup: Constructors {
		CConvexHull() = default;
		~CConvexHull() override;
		CConvexHull(const CConvexHull& a_Rhs);
		CConvexHull(CConvexHull&& a_Rhs) noexcept;
		//}

		//Subgroup: Operators {
		CConvexHull& operator=(CConvexHull&& a_Rhs);
		CConvexHull& operator=(const CConvexHull& a_Rhs);
		//}

		//Subgroup: Other {
		void BuildHull(const std::vector<float>& a_Vertices, const std::vector<unsigned int>& a_Indices, const std::vector<int>& a_Triangles);
		CVector3 Support(const CVector3& a_V, const CVector3& a_Position) override;
		//}
	private:
		std::map<unsigned int, std::shared_ptr<CVertex>> m_Vertices;
		ESHAPE_TYPE m_Type = ESHAPE_TYPE::SHAPE_CONVEX_HULL;

	};

}
