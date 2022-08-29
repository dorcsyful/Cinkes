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

    CVector3 barycentric = ProjectToTriangle(a_Contact->m_PenetrationDepth, a_Contact->m_Triangle[0]);
    CVector3 relatives[3];
    CTriangle triangleA = a_Contact->m_Triangle[1];
    CTriangle triangleB = a_Contact->m_Triangle[2];
    CTriangle triangleC = a_Contact->m_Triangle[0];
    relatives[0] = triangleA[0] * barycentric[0] + triangleA[1] * barycentric[1] + triangleA[2] * barycentric[2];
    relatives[1] = triangleB[0] * barycentric[0] + triangleB[1] * barycentric[1] + triangleB[2] * barycentric[2];
    CVector3 point_a = a_Contact->m_First->GetTransform().getBasis() * relatives[0];
    CVector3 point_b = a_Contact->m_First->GetTransform().getBasis() * relatives[1];
    a_Contact->m_ContactPoints.push_back(point_a);
    a_Contact->m_RelativeContactPosition[0].push_back(point_a);
    a_Contact->m_RelativeContactPosition[1].push_back(point_b);
}

Cinkes::CVector3 Cinkes::CContactPointCalculator::GetBaryCentric(const CVector3& a_Point, const CTriangle& a_Triangle)
{
    CVector3 barycentric;
    CVector3 tri0 = a_Triangle[0];
    CVector3 tri1 = a_Triangle[1];
    CVector3 tri2 = a_Triangle[2];

    CVector3 v0 = a_Triangle[1] - a_Triangle[2];
    CVector3 v1 = a_Triangle[2] - a_Triangle[0];
    CVector3 v2 = a_Point - a_Triangle[0];
    float d00 = CVector3::Dot(v0, v0);
    float d01 = CVector3::Dot(v0, v1);
    float d11 = CVector3::Dot(v1, v1);
    float d20 = CVector3::Dot(v2, v0);
    float d21 = CVector3::Dot(v2, v1);
    float denom = d00 * d11 - d01 * d01;
    barycentric[0] = (d11 * d20 - d01 * d21) / denom;
    barycentric[1] = (d00 * d21 - d01 * d20) / denom;
    barycentric[2] = 1.0f - barycentric[0] - barycentric[1];
    return barycentric;
}

Cinkes::CVector3 Cinkes::CContactPointCalculator::ProjectToTriangle(CScalar a_Distance, const CTriangle& a_Triangle)
{
    CVector3 a = a_Triangle[0];
    CVector3 b = a_Triangle[1];
    CVector3 c = a_Triangle[2];

    // Calculate the barycentric coordinates of the origin (0,0,0) projected
    // onto the plane of the triangle.
    // 
    // [W. Heidrich, Journal of Graphics, GPU, and Game Tools,Volume 10, Issue 3, 2005.]
// u=P2?P1
    CVector3 u = b - a;
    // v=P3?P1
    CVector3 v = c - a;
    // n=u×v
    CVector3 n = u.Cross(v);
    // w=P?P1
    CVector3 w = CVector3(0, 0, 0) - a;
    // Barycentric coordinates of the projection P?of P onto T:
    // ?=[(u×w)?n]/n?
    CScalar gamma = u.Cross(w).Dot(n) / n.Dot(n);
    // ?=[(w×v)?n]/n?
    CScalar beta = w.Cross(v).Dot(n) / n.Dot(n);
    CScalar alpha = 1 - gamma - beta;


    // Clamp the projected barycentric coordinates to lie within the triangle,
    // such that the clamped coordinates are closest (euclidean) to the original point.
    //
    // [https://math.stackexchange.com/questions/
    //  1092912/find-closest-point-in-triangle-given-barycentric-coordinates-outside]
    CScalar t;
    if (alpha >= 0.0 && beta < 0.0)
    {
        t = a.Dot(u);
        if ((gamma < 0.0) && (t > 0.0))
        {
            beta = std::min(static_cast<CScalar>(1.0), t / u.Length2());
            alpha = 1.0 - beta;
            gamma = 0.0;
        }
        else
        {
            gamma = std::min(static_cast<CScalar>(1.0), std::max(static_cast<CScalar>(0), a.Dot(v) / v.Length2()));
            alpha = 1.0 - gamma;
            beta = 0.0;
        }
    }
    else if (beta >= 0.0 && gamma < 0.0)
    {
        w = b - c;
        t = b.Dot(w);
        if ((alpha < 0.0) && (t > 0.0))
        {
            gamma = std::min(static_cast<CScalar>(1.0), t / w.Length2());
            beta = 1.0 - gamma;
            alpha = 0.0;
        }
        else
        {
            alpha = std::min(static_cast<CScalar>(1.0), std::max(static_cast<CScalar>(0), -(b.Dot(u)) / u.Length2()));
            beta = 1.0 - alpha;
            gamma = 0.0;
        }
    }
    else if (gamma >= 0.0 && alpha < 0.0)
    {
        w = b, c;
        t = -(c.Dot(v));
        if ((beta < 0.0) && (t > 0.0))
        {
            alpha = std::min(static_cast<CScalar>(1.0), t / v.Length2());
            gamma = 1.0 - alpha;
            beta = 0.0;
        }
        else
        {
            beta = std::min(static_cast<CScalar>(1.0), std::max(static_cast<CScalar>(0), -(c.Dot(w)) / w.Length()));
            gamma = 1.0 - beta;
            alpha = 0.0;
        }
    }

    return CVector3(alpha, beta, gamma);
}

