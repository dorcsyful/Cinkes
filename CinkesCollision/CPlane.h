#pragma once
#include "CVector3.h"
namespace Cinkes {
	struct CPlane {
		CPlane() = default;
		CPlane(const CVector3& a_Normal, CVector3 a_Point) 
		{
			normal = a_Normal;
			distance = -(a_Normal.Dot(a_Point));
		}

		CScalar DistanceToPoint(CVector3 a_Point) const { return normal.Dot(a_Point) + distance; }

		CVector3 Intersection(CVector3 p1, CVector3 p2) const {
			//Return the intersection point of a line passing two points and this plane
			return p1 + (p2 - p1) * (-DistanceToPoint(p1) / normal.Dot((p2 - p1)));
		};
		CVector3 normal;
		CVector3 point;
		CScalar distance; //used in case of infinite planes
	};
}