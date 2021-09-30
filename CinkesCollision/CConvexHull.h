#pragma once
#include "CCollisionShape.h"

namespace Cinkes
{
	class CConvexHull : CCollisionShape
	{
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
		void BuildHull();
		//}
	};

}
