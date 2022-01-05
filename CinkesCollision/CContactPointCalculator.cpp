#include "CContactPointCalculator.h"
#include "CBoxShape.h"
#include "CCollisionObject.h"
#include "CCollisionShape.h"
#include "CSphereShape.h"


void Cinkes::CContactPointCalculator::GetPoints(CContactInfo* a_Contact)
{
	if(a_Contact->m_First->GetCollisionShape()->GetType() == ESHAPE_TYPE::SHAPE_SPHERE &&
		a_Contact->m_Second->GetCollisionShape()->GetType() == ESHAPE_TYPE::SHAPE_SPHERE)
	{
		SphereSphere(a_Contact);
	}
	else if (a_Contact->m_First->GetCollisionShape()->GetType() == ESHAPE_TYPE::SHAPE_BOX &&
		a_Contact->m_Second->GetCollisionShape()->GetType() == ESHAPE_TYPE::SHAPE_BOX)
	{
		BoxBox(a_Contact);
	}
	else
	{
		SphereBox(a_Contact);
	}
}

void Cinkes::CContactPointCalculator::SphereSphere(CContactInfo* a_Contact)
{
	a_Contact->m_ContactPoints.emplace_back();
	CVector3 addition = a_Contact->m_First->GetTransform().getOrigin() - a_Contact->m_Second->GetTransform().getOrigin();
	addition *= static_cast<CScalar>(0.5);
	a_Contact->m_ContactPoints[0] = a_Contact->m_First->GetTransform().getOrigin() + addition;
}

void Cinkes::CContactPointCalculator::SphereBox(CContactInfo* a_Contact)
{
	//the normal points from the "first" to the second
	CVector3 normal;
	CVector3 radius;
	CCollisionObject* object;
	if(a_Contact->m_First->GetCollisionShape()->GetType() == ESHAPE_TYPE::SHAPE_SPHERE)
	{
		object = a_Contact->m_First.get();
		normal = a_Contact->m_Normal;
		radius = dynamic_cast<CBoxShape*>(object->GetCollisionShape().get())->GetDimensions();
		a_Contact->m_ContactPoints.emplace_back(object->GetTransform().getOrigin() +(CVector3(normal * radius)));

	} else
	{
		object = a_Contact->m_Second.get();
		normal = a_Contact->m_Normal * (-1);
		radius = dynamic_cast<CBoxShape*>(object->GetCollisionShape().get())->GetDimensions();
		a_Contact->m_ContactPoints.emplace_back(object->GetTransform().getOrigin() + (CVector3(normal * radius)));
	}

}

void Cinkes::CContactPointCalculator::BoxBox(CContactInfo* a_Contact)
{
	//a_Contact->m_ContactPoints = a_Contact->m_First->GetCollisionShape()->SupportPointsForContact(a_Contact->m_Normal, a_Contact->m_First->GetTransform());
}

