#pragma once
#include "CVector3.h"
#include "CPoint.h"
namespace Cinkes {
	struct CPlane {
		CPlane(const CPoint& a_Normal, CScalar a_Distance) 
		{
			normal = a_Normal;
			distance = a_Distance;
		}
		CPlane(CPoint a_X, CPoint a_Y, CPoint a_Z) { 
			point[0] = a_X;
			point[1] = a_Y;
			point[2] = a_Z;
		}

		CPoint Intersection(CPoint p1, CPoint p2) const {
			//Return the intersection point of a line passing two points and this plane
			return p1 + (p2 - p1) * (-DistanceToPoint(p1) / normal.coords.Dot((p2 - p1).coords));
		};

		CScalar DistanceToPoint(CPoint a_Point) const { return normal.coords.Dot(a_Point.coords) + distance; }

		CPoint normal;
		CPoint point[3]; //used in case of a triangle
		CScalar distance; //used in case of infinite planes
	};
}