#pragma once
#include "CVector3.h"

namespace Cinkes {
	struct CPlane {
		CPlane(CVector3 a_Normal, CVector3 a_Point) 
		{
			normal = a_Normal;
			point = a_Point;
			distance = point.Length();
		}
		CVector3 normal;
		CVector3 point;
		CScalar distance;
	};
}