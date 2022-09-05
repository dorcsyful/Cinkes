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
	for (size_t i = m_Contacts.size() - 1; i >= 0; i--) {
		if (!UpdateManifold(m_Contacts[i].get())) {
			m_Contacts.erase(std::find(m_Contacts.begin(), m_Contacts.end(), m_Contacts[i]));
		}
	}

	m_BVH->Update();
	for (auto& element : m_BVH->m_Contacts)
	{
		for (unsigned i = 0; i < element->m_Objects.size() - 1; i++) {
			CSimplex simplex;
			bool algorithm = m_GJK->Algorithm(element->m_Objects[i].get(), element->m_Objects[i + 1].get(),simplex);
			if(algorithm && !IsPersistent(element->m_Objects[i].get(), element->m_Objects[i + 1].get()))
			{
				std::shared_ptr<CContactInfo> contact = std::make_shared<CContactInfo>();
				contact->m_First = element->m_Objects[i];
				element->m_Objects[i]->SetHasContact(contact.get());
				element->m_Objects[i + 1]->SetHasContact(contact.get());
				contact->m_Second = element->m_Objects[i + 1];
				m_CEPA->Run(contact.get(), simplex);
				m_Contacts.push_back(contact);
				m_ContactPointCalculator->GetPoints(m_Contacts[m_Contacts.size() - 1].get());
			}
		}
	}
	m_BVH->m_Contacts.clear();
}

bool Cinkes::CCollisionWorld::IsPersistent(CCollisionObject* a_ObjectA, CCollisionObject* a_ObjectB)
{
	for (auto& current : m_Contacts) {
		if (current->m_First.get() == a_ObjectA || current->m_Second.get() == a_ObjectA) {
			if (current->m_First.get() == a_ObjectB || current->m_Second.get() == a_ObjectB) {
				return true;
			}
		}
	}
	return false;
}

bool Cinkes::CCollisionWorld::UpdateManifold(CContactInfo* a_Contact)
{
	CSimplex simplex;
	bool algorithm = m_GJK->Algorithm(a_Contact->m_First.get(), a_Contact->m_Second.get(), simplex);
	if (algorithm) {
		m_CEPA->Run(a_Contact, simplex);
		m_ContactPointCalculator->GetPoints(a_Contact);
	}
	size_t last = a_Contact->m_RelativeContactPosition[0].size();
	CVector3 value = a_Contact->m_RelativeContactPosition[0].back();
	for (size_t i = 0; i < last; i++) {
		if ((a_Contact->m_RelativeContactPosition[0][i] - value).Length() < 0.001) {
			a_Contact->m_RelativeContactPosition[0][i] = value;
			a_Contact->m_RelativeContactPosition[1][i] = a_Contact->m_RelativeContactPosition[1].back();
			a_Contact->m_RelativeContactPosition[0].erase(a_Contact->m_RelativeContactPosition[0].end() - 1);
			a_Contact->m_RelativeContactPosition[1].erase(a_Contact->m_RelativeContactPosition[1].end() - 1);
			break;
		}
	}
}
