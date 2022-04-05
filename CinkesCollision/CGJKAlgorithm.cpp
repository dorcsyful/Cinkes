#include "CGJKAlgorithm.h"

#include <iostream>

#include "CCollisionObject.h"
#include "CCollisionShape.h"
#include "CSimplex.h"
#include "../CinkesMath/CVector3.h"

bool Cinkes::CGJKAlgorithm::Algorithm(CCollisionObject* a_Object1, CCollisionObject* a_Object2, CSimplex& a_Simplex)
{
    CVector3 A = a_Object1->GetCollisionShape()->Support(CVector3(1, 0, 0));
    CVector3 B = a_Object2->GetCollisionShape()->Support(CVector3(-1, 0, 0));
    CVector3 support = (A + a_Object1->GetTransform().getOrigin()) - (B + a_Object2->GetTransform().getOrigin());

    CSimplex simplex;
    simplex.Push_Front(support);
    simplex.Push_FrontA(A);
    simplex.Push_FrontB(B);
    CVector3 next = support * (-1);

    while(true)
    {
        next.Normalize();
    	A = a_Object1->GetCollisionShape()->Support(next);
    	B = a_Object2->GetCollisionShape()->Support(next * (-1));
    	support = (A + a_Object1->GetTransform().getOrigin()) - (B + a_Object2->GetTransform().getOrigin());

        std::cout << support.Length() << std::endl;
    	if(support.Dot(next) <= 0)
        {
            a_Simplex = simplex;
	        return false;
        }

        simplex.Push_Front(support);
        simplex.Push_FrontA(A);
        simplex.Push_FrontB(B);

        if(NextSimplex(simplex, next))
        {
            a_Simplex = simplex;
        	return true;
        }
    }

}

bool Cinkes::CGJKAlgorithm::NextSimplex(CSimplex& a_Simplex, CVector3& a_Direction)
{
	switch (a_Simplex.Size())
	{
    case 2: return Line(a_Simplex, a_Direction);
    case 3: return Triangle(a_Simplex, a_Direction);
    case 4: return Tetrahedron(a_Simplex, a_Direction);
    default: return false;
	}
}

bool Cinkes::CGJKAlgorithm::Line(CSimplex& a_Simplex, CVector3& a_Direction)
{
    CVector3 a = a_Simplex[0];
    CVector3 b = a_Simplex[1];
    CVector3 ab = b - a;
    CVector3 ao = a * (-1);

	if(SameDirection(ab, ao))
    {
        a_Direction = ab.Cross(ao).Cross(ab);
    } else
    {
        a_Simplex.SetAllA({ a_Simplex.getPointA(0) });
        a_Simplex.SetAllB({ a_Simplex.getPointB(0) });
	    a_Simplex = { a };
	    a_Direction = ao;
    }


    return false;
}

bool Cinkes::CGJKAlgorithm::Triangle(CSimplex& a_Simplex, CVector3& a_Direction)
{
    CVector3 a = a_Simplex[0];
    CVector3 b = a_Simplex[1];
    CVector3 c = a_Simplex[2];
    CVector3 ab = b - a;
    CVector3 ac = c - a;
    CVector3 ao = a * (-1);
    CVector3 abc = ab.Cross(ac);

    if(SameDirection(abc.Cross(ac),ao))
    {
	    if(SameDirection(ac, ao))
	    {
            a_Simplex.SetAllA({ a_Simplex.getPointA(0),a_Simplex.getPointA(2) });
            a_Simplex.SetAllB({ a_Simplex.getPointB(0),a_Simplex.getPointB(2) });
            a_Simplex = { a,c };
            a_Direction = ac.Cross(ao).Cross(ac);
	    }
        else
        {
            a_Simplex.SetAllA({ a_Simplex.getPointA(0),a_Simplex.getPointA(1) });
            a_Simplex.SetAllB({ a_Simplex.getPointB(0),a_Simplex.getPointB(1) });
            a_Simplex = { a,b };
            return Line(a_Simplex, a_Direction);
        }
    }
    else
    {
        if (SameDirection(ab.Cross(abc), ao))
        {
            a_Simplex.SetAllA({ a_Simplex.getPointA(0),a_Simplex.getPointA(1) });
            a_Simplex.SetAllB({ a_Simplex.getPointB(0),a_Simplex.getPointB(1) });
            a_Simplex = { a,b };
            return Line(a_Simplex, a_Direction);
        }
        else
        {
            if (SameDirection(abc, ao))
            {
                a_Direction = abc;
            }
            else
            {
                a_Simplex.SetAllA({ a_Simplex.getPointA(0),a_Simplex.getPointA(2), a_Simplex.getPointA(1) });
                a_Simplex.SetAllB({ a_Simplex.getPointB(0),a_Simplex.getPointB(2), a_Simplex.getPointB(1) });
                a_Simplex = { a,c,b };
                a_Direction = abc * (-1);
            }
        }
    }
    return false;
}

bool Cinkes::CGJKAlgorithm::Tetrahedron(CSimplex& a_Simplex, CVector3& a_Direction)
{
    CVector3 a = a_Simplex[0];
    CVector3 b = a_Simplex[1];
    CVector3 c = a_Simplex[2];
    CVector3 d = a_Simplex[3];
    CVector3 ab = b - a;
    CVector3 ac = c - a;
    CVector3 ad = d - a;
    CVector3 ao = a * (-1);
    CVector3 abc = ab.Cross(ac);
    CVector3 acd = ac.Cross(ad);
    CVector3 adb = ad.Cross(ab);

    if(SameDirection(abc, ao))
    {
        a_Simplex.SetAllA({ a_Simplex.getPointA(0),a_Simplex.getPointA(1), a_Simplex.getPointA(2) });
        a_Simplex.SetAllB({ a_Simplex.getPointB(0),a_Simplex.getPointB(1), a_Simplex.getPointB(2) });
        a_Simplex = { a,b,c };
        return Triangle(a_Simplex, a_Direction);
    }
    if(SameDirection(acd, ao))
    {
        a_Simplex.SetAllA({ a_Simplex.getPointA(0),a_Simplex.getPointA(2), a_Simplex.getPointA(3) });
        a_Simplex.SetAllB({ a_Simplex.getPointB(0),a_Simplex.getPointB(2), a_Simplex.getPointB(3) });
        a_Simplex = { a,c,d };
        return Triangle(a_Simplex, a_Direction);
    }
    if(SameDirection(adb, ao))
    {
        a_Simplex.SetAllA({ a_Simplex.getPointA(0),a_Simplex.getPointA(3), a_Simplex.getPointA(1) });
        a_Simplex.SetAllB({ a_Simplex.getPointB(0),a_Simplex.getPointB(3), a_Simplex.getPointB(1) });
        a_Simplex = { a,d,b };
        return Triangle(a_Simplex, a_Direction);
    }
    return true;
}

bool Cinkes::CGJKAlgorithm::SameDirection(const CVector3& a_Direction, const CVector3& a_AO)
{
    return a_Direction.Dot(a_AO) > 0;
}
