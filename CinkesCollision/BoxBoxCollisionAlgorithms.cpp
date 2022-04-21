// ReSharper disable CppClangTidyCppcoreguidelinesProTypeStaticCastDowncast
#include "BoxBoxCollisionAlgorithms.h"

#include <cassert>

#include "CCollisionObject.h"
#include "CContactInfo.h"
#include "CUtils.h"
#include "CVector3.h"
#include "CBoxShape.h"

bool Cinkes::BoxBoxCollisionAlgorithms::CalculateCurrent(CContactInfo* a_ContactInfo)
{
    CCollisionObject& first = *a_ContactInfo->m_First;
    CCollisionObject& second = *a_ContactInfo->m_Second;
    BoxAndBox(first, second, a_ContactInfo);
    return true;
}

inline bool Cinkes::BoxBoxCollisionAlgorithms::TryAxis(const CCollisionObject& a_One, const CCollisionObject& a_Two, CVector3 a_Axis, const CVector3& a_ToCentre, unsigned a_Index, CScalar& a_SmallestPenetration, unsigned& a_SmallestCase)
{
    // Make sure we have a normalized axis, and don't check almost parallel axes
    if (a_Axis.Length2() < static_cast<CScalar>(0.0001)) return true;
    a_Axis.Normalize();

    CScalar penetration = PenetrationOnAxis(a_One, a_Two, a_Axis, a_ToCentre);

    if (penetration < 0) return false;
    if (penetration < a_SmallestPenetration) {
        a_SmallestPenetration = penetration;
        a_SmallestCase = a_Index;
    }
    return true;
}

CScalar Cinkes::BoxBoxCollisionAlgorithms::PenetrationOnAxis(const CCollisionObject& a_One, const CCollisionObject& a_Two, const CVector3& a_Axis, const CVector3& a_ToCentre)
{
    // Project the half-size of one onto axis
    CScalar oneProject = TransformToAxis(a_One, a_Axis);
    CScalar twoProject = TransformToAxis(a_Two, a_Axis);

    // Project this onto the axis
    CScalar distance = CUtils::Abs(a_ToCentre.getX() * a_Axis.getX() + a_ToCentre.getY() * a_Axis.getY() + a_ToCentre.getZ() * a_Axis.getZ());

    // Return the overlap (i.e. positive indicates
    // overlap, negative indicates separation).
    return oneProject + twoProject - distance;
}

CScalar Cinkes::BoxBoxCollisionAlgorithms::TransformToAxis(const CCollisionObject& a_Object, const CVector3& a_Axis)
{
    CBoxShape* shape = static_cast<CBoxShape*>(a_Object.GetCollisionShape().get());
    return
        shape->GetDimensions().getX() * CUtils::Abs(a_Axis.Dot(a_Object.GetTransform().getAxisVector(0))) +
        shape->GetDimensions().getY() * CUtils::Abs(a_Axis.Dot(a_Object.GetTransform().getAxisVector(1))) +
        shape->GetDimensions().getZ() * CUtils::Abs(a_Axis.Dot(a_Object.GetTransform().getAxisVector(2)));

}

bool Cinkes::BoxBoxCollisionAlgorithms::OverlapOnAxis(const CCollisionObject& a_One, const CCollisionObject& a_Two, const CVector3& a_Axis, const CVector3& a_ToCentre)
{
    // Project the half-size of one onto axis
    CScalar oneProject = TransformToAxis(a_One, a_Axis);
    CScalar twoProject = TransformToAxis(a_Two, a_Axis);

    // Project this onto the axis
    CScalar distance = CUtils::Abs(a_ToCentre.Dot(a_Axis));

    // Check for overlap
    return (distance < oneProject + twoProject);

}
#define CHECK_OVERLAP(axis, index) \
    if (!TryAxis(a_One, a_Two, (axis), toCentre, (index), pen, best)) return 0;

unsigned Cinkes::BoxBoxCollisionAlgorithms::BoxAndBox(const CCollisionObject& a_One, const CCollisionObject& a_Two, CContactInfo* a_Data)
{
    // Find the vector between the two centres
    CVector3 toCentre = a_Two.GetTransform().getAxisVector(3) - a_One.GetTransform().getAxisVector(3);

    // We start assuming there is no contact
    CScalar pen = std::numeric_limits<CScalar>::max();
    unsigned best = 0xffffff;

    // Now we check each axes, returning if it gives us
    // a separating axis, and keeping track of the axis with
    // the smallest penetration otherwise.
    CHECK_OVERLAP(a_One.GetTransform().getAxisVector(0), 0)
    CHECK_OVERLAP(a_One.GetTransform().getAxisVector(1), 1)
    CHECK_OVERLAP(a_One.GetTransform().getAxisVector(2), 2)

    CHECK_OVERLAP(a_Two.GetTransform().getAxisVector(0), 3)
    CHECK_OVERLAP(a_Two.GetTransform().getAxisVector(1), 4)
    CHECK_OVERLAP(a_Two.GetTransform().getAxisVector(2), 5)

    // Store the best axis-major, in case we run into almost
    // parallel edge collisions later
    unsigned bestSingleAxis = best;

    CHECK_OVERLAP(a_One.GetTransform().getAxisVector(0).Cross(a_Two.GetTransform().getAxisVector(0)), 6)
    CHECK_OVERLAP(a_One.GetTransform().getAxisVector(0).Cross(a_Two.GetTransform().getAxisVector(1)), 7)
    CHECK_OVERLAP(a_One.GetTransform().getAxisVector(0).Cross(a_Two.GetTransform().getAxisVector(2)), 8)
    CHECK_OVERLAP(a_One.GetTransform().getAxisVector(1).Cross(a_Two.GetTransform().getAxisVector(0)), 9)
    CHECK_OVERLAP(a_One.GetTransform().getAxisVector(1).Cross(a_Two.GetTransform().getAxisVector(1)), 10)
    CHECK_OVERLAP(a_One.GetTransform().getAxisVector(1).Cross(a_Two.GetTransform().getAxisVector(2)), 11)
    CHECK_OVERLAP(a_One.GetTransform().getAxisVector(2).Cross(a_Two.GetTransform().getAxisVector(0)), 12)
    CHECK_OVERLAP(a_One.GetTransform().getAxisVector(2).Cross(a_Two.GetTransform().getAxisVector(1)), 13)
    CHECK_OVERLAP(a_One.GetTransform().getAxisVector(2).Cross(a_Two.GetTransform().getAxisVector(2)), 14)

    // Make sure we've got a result.
    assert(best != 0xffffff);

    // We now know there's a collision, and we know which
    // of the axes gave the smallest penetration. We now
    // can deal with it in different ways depending on
    // the case.
    if (best < 3)
    {
        // We've got a vertex of box two on a face of box one.
        FillPointFaceBoxBox(a_One, a_Two, toCentre, a_Data, best, pen);
        return 1;
    }
    if (best < 6)
    {
	    // We've got a vertex of box one on a face of box two.
	    // We use the same algorithm as above, but swap around
	    // one and two (and therefore also the vector between their
	    // centres).
	    FillPointFaceBoxBox(a_Two, a_One, toCentre * -1.0f, a_Data, best - 3, pen);
	    return 1;
    }
    // We've got an edge-edge contact. Find out which axes
    best -= 6;
    unsigned oneAxisIndex = best / 3;
    unsigned twoAxisIndex = best % 3;
    CVector3 oneAxis = a_One.GetTransform().getAxisVector(oneAxisIndex);
    CVector3 twoAxis = a_Two.GetTransform().getAxisVector(twoAxisIndex);
    CVector3 axis = oneAxis.Cross(twoAxis);
    axis.Normalize();

    // The axis should point from box one to box two.
    if (axis.Dot(toCentre) > 0) axis = axis * -1.0f;

    // We have the axes, but not the edges: each axis has 4 edges parallel
    // to it, we need to find which of the 4 for each object. We do
    // that by finding the point in the centre of the edge. We know
    // its component in the direction of the box's collision axis is zero
    // (its a mid-point) and we determine which of the extremes in each
    // of the other axes is closest.
    CVector3 ptOnOneEdge = static_cast<CBoxShape*>(a_One.GetCollisionShape().get())->GetDimensions();
    CVector3 ptOnTwoEdge = static_cast<CBoxShape*>(a_Two.GetCollisionShape().get())->GetDimensions();
    for (unsigned i = 0; i < 3; i++)
    {
	    if (i == oneAxisIndex) ptOnOneEdge[i] = 0;
	    else if (a_One.GetTransform().getAxisVector(i).Dot(axis) > 0) ptOnOneEdge[i] = -ptOnOneEdge[i];

	    if (i == twoAxisIndex) ptOnTwoEdge[i] = 0;
	    else if (a_Two.GetTransform().getAxisVector(i).Dot(axis) < 0) ptOnTwoEdge[i] = -ptOnTwoEdge[i];
    }

    // Move them into world coordinates (they are already oriented
    // correctly, since they have been derived from the axes).
    ptOnOneEdge = a_One.GetTransform() * ptOnOneEdge;
    ptOnTwoEdge = a_Two.GetTransform() * ptOnTwoEdge;

    // So we have a point and a direction for the colliding edges.
    // We need to find out point of closest approach of the two
    // line-segments.
    CVector3 vertex = ContactPoint(
	    ptOnOneEdge, oneAxis, static_cast<CBoxShape*>(a_One.GetCollisionShape().get())->GetDimensions()[oneAxisIndex],
	    ptOnTwoEdge, twoAxis, static_cast<CBoxShape*>(a_Two.GetCollisionShape().get())->GetDimensions()[twoAxisIndex],
	    bestSingleAxis > 2
    );

    // We can fill the contact.

    //a_Data->m_PenetrationDepth = pen;
    a_Data->m_Normal = axis;
    a_Data->m_ContactPoints.push_back(vertex);
    return 1;
}

void Cinkes::BoxBoxCollisionAlgorithms::FillPointFaceBoxBox(const CCollisionObject& a_One, const CCollisionObject& a_Two, const CVector3& a_ToCentre, CContactInfo* a_Data, unsigned a_Best, CScalar a_Pentration)
{
    // This method is called when we know that a vertex from
    // box two is in contact with box one.


    // We know which axis the collision is on (i.e. best),
    // but we need to work out which of the two faces on
    // this axis.
    CVector3 normal = a_One.GetTransform().getAxisVector(a_Best);
    if (a_One.GetTransform().getAxisVector(a_Best).Dot(a_ToCentre) > 0)
    {
        normal = normal * -1.0f;
    }

    // Work out which vertex of box two we're colliding with.
    // Using toCentre doesn't work!
    CVector3 vertex = static_cast<CBoxShape*>(a_One.GetCollisionShape().get())->GetDimensions();
    if (a_Two.GetTransform().getAxisVector(0).Dot(normal) < 0) vertex[0] = vertex.getX() * -1;
    if (a_Two.GetTransform().getAxisVector(1).Dot(normal) < 0) vertex[1] = vertex.getY() * -1;
    if (a_Two.GetTransform().getAxisVector(2).Dot(normal) < 0) vertex[2] = vertex.getZ() * -1;

    // Create the contact data
    a_Data->m_Normal = normal;
    //a_Data->m_PenetrationDepth = a_Pentration;
    a_Data->m_ContactPoints.push_back(a_Two.GetTransform() * vertex);
}

Cinkes::CVector3 Cinkes::BoxBoxCollisionAlgorithms::ContactPoint(const CVector3& a_POne, const CVector3& a_DOne, CScalar a_OneSize, const CVector3& a_PTwo, const CVector3& a_DTwo, CScalar a_TwoSize, bool a_UseOne)
{
    CVector3 toSt, cOne, cTwo;
    CScalar dpStaOne, dpStaTwo, dpOneTwo, smOne, smTwo;
    CScalar denom, mua, mub;

    smOne = a_DOne.Length2();
    smTwo = a_DTwo.Length2();
    dpOneTwo = a_DTwo.Dot(a_DOne);

    toSt = a_POne - a_PTwo;
    dpStaOne = a_DOne.Dot(toSt);
    dpStaTwo = a_DTwo.Dot(toSt);

    denom = smOne * smTwo - dpOneTwo * dpOneTwo;

    // Zero denominator indicates parrallel lines
    if (CUtils::Abs(denom) < 0.0001f) {
        return a_UseOne ? a_POne : a_PTwo;
    }

    mua = (dpOneTwo * dpStaTwo - smTwo * dpStaOne) / denom;
    mub = (smOne * dpStaTwo - dpOneTwo * dpStaOne) / denom;

    // If either of the edges has the nearest point out
    // of bounds, then the edges aren't crossed, we have
    // an edge-face contact. Our point is on the edge, which
    // we know from the useOne parameter.
    if (mua > a_OneSize ||
        mua < a_OneSize * -1 ||
        mub > a_TwoSize ||
        mub < a_TwoSize * -1)
    {
        return a_UseOne ? a_POne : a_PTwo;
    }
    else
    {
        cOne = a_POne + a_DOne * mua;
        cTwo = a_PTwo + a_DTwo * mub;

        return cOne * 0.5 + cTwo * 0.5;
    }
}
