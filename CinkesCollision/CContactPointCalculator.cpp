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
	CVector3 barycentric = GetBaryCentric(a_Contact->m_PenetrationPoint, a_Contact->m_Triangle[0]);
	a_Contact->m_RelativeContactPosition[0] = CVector3(a_Contact->m_Triangle[1][0] * barycentric[0] + a_Contact->m_Triangle[1][1] * barycentric[1] +
		a_Contact->m_Triangle[1][2] * barycentric[2]);
	a_Contact->m_RelativeContactPosition[1] = CVector3(a_Contact->m_Triangle[2][0] * barycentric[0] + a_Contact->m_Triangle[2][1] * barycentric[1] +
		a_Contact->m_Triangle[2][2] * barycentric[2]);
}

Cinkes::CVector3 Cinkes::CContactPointCalculator::GetBaryCentric(const CVector3& a_Distance, const CTriangle& a_Triangle)
{
	CVector3 returnValue;
	CVector3 v0 = a_Triangle[1] - a_Triangle[0];
	CVector3 v1 = a_Triangle[2] - a_Triangle[0];
	CVector3 v2 = a_Distance - a_Triangle[0];
	float d00 = v0.Length2();
	float d01 = v0.Dot(v1);
	float d11 = v1.Length2();
	float d20 = v2.Dot(v0);
	float d21 = v2.Dot(v1);
	float denom = d00 * d11 - d01 * d01;
	returnValue[1] = (d11 * d20 - d01 * d21) / denom;
	returnValue[2] = (d00 * d21 - d01 * d20) / denom;
	returnValue[0] = 1.0f - returnValue[1] - returnValue[2];
	return returnValue;
}