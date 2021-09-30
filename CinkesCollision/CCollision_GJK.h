#pragma once
#include "CCollisionShape.h"

namespace Cinkes
{

	static class CCollision_GJK
	{
	public:
		Cinkes::CCollisionShape* MinkowskiDifference();
	};
}
