#include "CCollisionWorld.h"

#include <functional>

#include "CCollisionObject.h"
#include "CBVH.h"
#include "CEPA.h"
#include "CGJKAlgorithm.h"

Cinkes::CCollisionWorld::CCollisionWorld() : m_ShouldUpdate(false)
{
	m_BVH = std::make_unique<CBVH>(m_Objects);
	m_GJK = std::make_unique<CGJKAlgorithm>();
	m_CEPA = std::make_unique<CEPA>();
	m_ContactPointCalculator = std::make_unique<CContactPointCalculator>();

	m_Boxes = std::make_unique<BoxBoxCollisionAlgorithms>();
}


Cinkes::CCollisionWorld& Cinkes::CCollisionWorld::operator=(const CCollisionWorld& a_Rhs)
{
	for (const auto& object : a_Rhs.m_Objects)
	{
		m_Objects.push_back(object);
	}
	m_BVH = std::make_unique<CBVH>(m_Objects);
	m_GJK = std::make_unique<CGJKAlgorithm>();
	m_CEPA = std::make_unique<CEPA>();
	m_ContactPointCalculator = std::make_unique<CContactPointCalculator>();
	return *this;
}

bool Cinkes::CCollisionWorld::AddObject(const std::shared_ptr<CCollisionObject>& a_Object)
{
	auto size = m_Objects.size();
	m_Objects.push_back(a_Object);
	if(size == m_Objects.size() - 1)
	{
		//TODO: find a better way to update objects inside the BVH class
		m_BVH->m_AABBs.push_back(m_BVH->CreateAABB(a_Object));
		return true;
	}

	return false;
}

bool Cinkes::CCollisionWorld::RemoveObject(const std::shared_ptr<CCollisionObject>& a_Object)
{
	auto removed = std::remove(m_Objects.begin(), m_Objects.end(), a_Object);

	if (removed == m_Objects.end())
	{
		a_Object->m_InRemoveQueue = true;
		return true;
	}
	return false;
}

bool Cinkes::CCollisionWorld::RemoveObjectByIndex(int a_Index)
{
	m_Objects[a_Index]->m_InRemoveQueue = true;
	auto size = m_Objects.size();
	m_Objects.erase(m_Objects.begin() + a_Index);

	if(size -1 ==m_Objects.size())
	{
		return true;
	}
	return false;
}

void Cinkes::CCollisionWorld::RunCollision(CScalar a_T)
{
	m_Contacts.clear();
	m_BVH->Update();
	for (auto& element : m_BVH->m_Contacts)
	{
		for (unsigned i = 0; i < element->m_Objects.size() - 1; i++) {
			CSimplex simplex;
			bool algorithm = m_GJK->Algorithm(element->m_Objects[i].get(), element->m_Objects[i + 1].get(),simplex);
			if(algorithm)
			{
				if (element->m_Objects[i]->GetType() == EOBJECT_TYPE::TYPE_RIGID || element->m_Objects[i + 1]->GetType() == EOBJECT_TYPE::TYPE_RIGID) {
					std::shared_ptr<CContactInfo> contact = std::make_shared<CContactInfo>();
					contact->m_First = element->m_Objects[i];
					element->m_Objects[i]->SetHasContact(contact.get());
					element->m_Objects[i + 1]->SetHasContact(contact.get());
					contact->m_Second = element->m_Objects[i + 1];
					m_CEPA->Run(contact, simplex);
					m_Contacts.push_back(contact);
					m_Boxes->CalculateCurrent(m_Contacts[m_Contacts.size() - 1].get());
					//m_ContactPointCalculator->GetPoints(m_Contacts[m_Contacts.size() - 1].get());
				}
			}
		}
	}
	m_BVH->m_Contacts.clear();
}
