#include "CGJKAlgorithm.h"

#include "CCollisionObject.h"
#include "CCollisionShape.h"
#include "CSimplex.h"
#include "../CinkesMath/CVector3.h"

bool Cinkes::CGJKAlgorithm::Algorithm(CCollisionObject* a_Object1, CCollisionObject* a_Object2)
{
    CVector3 dir = a_Object1->GetCollisionShape()->Support(CVector3(1, 0, 0)) - 
					a_Object2->GetCollisionShape()->Support(CVector3(1, 0, 0));

    CSimplex simplex;
    simplex.Push_Front(dir);

    CVector3 next = dir * (-1);

    while(true)
    {
        dir = a_Object1->GetCollisionShape()->Support(next) - a_Object2->GetCollisionShape()->Support(next);
        if(dir.Dot(next) <= 0)
        {
	        return false;
        }

        simplex.Push_Front(dir);

        if(NextSimplex(simplex, next))
        {
            return true;
        }
    }


    return false;
}

bool Cinkes::CGJKAlgorithm::NextSimplex(CSimplex a_Simplex, CVector3 a_Direction)
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

    if(ab == ao)
    {
        a_Direction = ab.Cross(ao).Cross(ab);
    }
    else
    {
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

    if(abc.Cross(ac) == ao)
    {
	    if(ac == ao)
	    {
            a_Simplex = { a,c };
            a_Direction = ac.Cross(ao).Cross(ac);
	    }
        else
        {
            return Line(a_Simplex = { a,b }, a_Direction);
        }
    }
    else
    {
	    if(ab.Cross(abc) == ao)
	    {
            return Line(a_Simplex = { a,b }, a_Direction);
	    } else
	    {
		    if(abc == ao)
		    {
                a_Direction = abc;
		    }
            else
            {
                a_Simplex = { a,b,c };
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

    if(abc == ao)
    {
        return Triangle(a_Simplex = { a,b,c }, a_Direction);
    }
    if(acd == ao)
    {
        return Triangle(a_Simplex = { a,c,d }, a_Direction);
    }
    if(adb == ao)
    {
        return Triangle(a_Simplex = { a,d,b }, a_Direction);
    }


    return true;
}
