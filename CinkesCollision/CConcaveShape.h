#pragma once
#include "CConvexHull.h"
namespace Cinkes
{

	class CConcaveShape : CCollisionShape
	{
	public:
		//Subgroup: Constructors {
		CConcaveShape();
		~CConcaveShape();
		CConcaveShape(const CConcaveShape& a_Rhs);
		CConcaveShape(CConcaveShape&& a_Rhs);
		//}

		//Subgroup: Operators {
		CConcaveShape& operator=(CConcaveShape&& a_Rhs);
		CConcaveShape& operator=(const CConcaveShape& a_Rhs);
		//}
	};

}
