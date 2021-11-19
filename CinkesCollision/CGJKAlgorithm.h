#pragma once
#include "CSimplex.h"
#include "../CinkesMath/CVector3.h"
#include "CCollisionObject.h"
namespace Cinkes
{
	class CCollisionObject;

	class CGJKAlgorithm
	{
	public:
		CGJKAlgorithm() = default;
		~CGJKAlgorithm() = default;
		CGJKAlgorithm(CGJKAlgorithm& a_Cgjk) = default;
		CGJKAlgorithm(CGJKAlgorithm&& a_Cgjk) = default;
		CGJKAlgorithm& operator=(const CGJKAlgorithm& a_Cgjk) = default;
		CGJKAlgorithm& operator=(CGJKAlgorithm&& a_Cgjk) = default;
		
		static bool Algorithm(CCollisionObject* a_Object1, CCollisionObject* a_Object2);
		static bool NextSimplex(CSimplex& a_Simplex, CVector3& a_Direction);
		static bool Line(CSimplex& a_Simplex, CVector3& a_Direction);
		static bool Triangle(CSimplex& a_Simplex, CVector3& a_Direction);
		static bool Tetrahedron(CSimplex& a_Simplex, CVector3& a_Direction);
		static bool SameDirection(const CVector3& a_Direction, const CVector3& a_AO);
	};
}
