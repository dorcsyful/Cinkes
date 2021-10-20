#pragma once
#include <map>
#include <vector>

#include "CCollisionShape.h"
#include "CVertex.h"

namespace Cinkes
{
	class CConvexHull : CCollisionShape
	{
	public:
		//Subgroup: Constructors {
		CConvexHull();
		~CConvexHull();
		CConvexHull(const CConvexHull& a_Rhs);
		CConvexHull(CConvexHull&& a_Rhs);
		//}

		//Subgroup: Operators {
		CConvexHull& operator=(CConvexHull&& a_Rhs);
		CConvexHull& operator=(const CConvexHull& a_Rhs);
		//}

		//Subgroup: Other {
		void BuildHull(const std::vector<float>& a_Vertices, const std::vector<unsigned int>& a_Indices, const std::vector<int>& a_Triangles);
		//}
	private:
		std::vector<CVertex*> m_Vertices;
	};

}
