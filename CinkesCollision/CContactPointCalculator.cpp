#include <algorithm>

#include "CContactPointCalculator.h"
#include "CBoxShape.h"
#include "CCollisionObject.h"
#include "CCollisionShape.h"
#include "CSphereShape.h"
#include "CSimplex.h"

void Cinkes::CContactPointCalculator::RunForAllContacts(std::vector<CContactInfo>& a_All)
{
	for(int i = 0; i < 4; i++)
	{
		GetPoints(&a_All[i]);
	}
}

void Cinkes::CContactPointCalculator::GetPoints(CContactInfo* a_Contact)
{
	CSimplex& simplex = a_Contact->m_Simplex;
    CVector3 barycentric = ProjectToTriangle(a_Contact->m_PenetrationDepth, a_Contact->m_Triangle[0]);
	a_Contact->m_RelativeContactPosition[0] = GetBaryCentric(barycentric, a_Contact->m_Triangle[1]);
	a_Contact->m_RelativeContactPosition[1] = GetBaryCentric(barycentric, a_Contact->m_Triangle[2]);
    a_Contact->m_ContactPoints.push_back(GetBaryCentric(barycentric, a_Contact->m_Triangle[0]));
}

Cinkes::CVector3 Cinkes::CContactPointCalculator::GetBaryCentric(const CVector3& a_Point, const CTriangle& a_Triangle)
{
    CMat3x3 matrix = CMat3x3(a_Triangle[0], a_Triangle[1], a_Triangle[2]);
    return matrix * a_Point;
}

Cinkes::CVector3 Cinkes::CContactPointCalculator::ProjectToTriangle(CScalar a_Distance, const CTriangle& a_Triangle)
{
    CVector3 a = a_Triangle[0];
    CVector3 b = a_Triangle[1];
    CVector3 c = a_Triangle[2];

    CVector3 u = a - b;
    CVector3 v = a - c;
    CVector3 w = u.Cross(a);

    CScalar t = a_Distance * a_Distance;
    CScalar z = CVector3::Dot(w, a_Triangle.m_Normal) / t;
    w = a.Cross(v);
    CScalar y = CVector3::Dot(w, a_Triangle.m_Normal) / t;
    CScalar x = 1.0 - z - y;

    return CVector3(x, y, z);
}

CScalar Cinkes::CContactPointCalculator::Clip(CScalar a_Original, CScalar a_Lower, CScalar a_Upper)
{
    return a_Original <= a_Lower ? a_Lower : a_Original >= a_Upper ? a_Upper : a_Original;

}
