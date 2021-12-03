#include "CBVH.h"

#include "CCollisionObject.h"
#include "CCollisionShape.h"

Cinkes::CBVH::CBVH(const std::vector<std::shared_ptr<CCollisionObject>>& a_Objects)
{
	for (auto& element : a_Objects)
	{
		m_AABBs.push_back(CreateAABB(element));
	}

	CalculateAxisLength();
}

std::shared_ptr<Cinkes::CAABB> Cinkes::CBVH::CreateAABB(const std::shared_ptr<CCollisionObject>& a_Object)
{
	std::shared_ptr<CAABB> temp = std::make_shared<CAABB>();
	CVector3 min, max;
	a_Object->GetCollisionShape()->CreateAABB(min, max);
	max += a_Object->GetTransform().getOrigin();
	min += a_Object->GetTransform().getOrigin();
	temp->m_Max[0] = static_cast<int>(max[0]);
	temp->m_Max[1] = static_cast<int>(max[1]);
	temp->m_Max[2] = static_cast<int>(max[2]);
	temp->m_Min[0] = static_cast<int>(min[0]);
	temp->m_Min[1] = static_cast<int>(min[1]);
	temp->m_Min[2] = static_cast<int>(min[2]);

	temp->m_Object = a_Object;

	temp->m_Object->m_AABBDirty = false;

	return temp;
}

void Cinkes::CBVH::CreateBVH(std::vector<std::shared_ptr<CAABB>>& a_Objects)
{
	m_RecurseCounter += 1;
	int min[3] = { std::numeric_limits<int>::max(), std::numeric_limits<int>::max() ,std::numeric_limits<int>::max() };
	int max[3] = { std::numeric_limits<int>::min(), std::numeric_limits<int>::min() ,std::numeric_limits<int>::min() };
	int midpoints[3] = { 0,0,0 };
	std::vector<std::shared_ptr<CAABB>> left;
	std::vector<std::shared_ptr<CAABB>> right;

	for (auto& elements : a_Objects)
	{
		for (int i = 0; i < 3; i++)
		{
			if (elements->m_Min[i] < min[i]) { min[i] = elements->m_Min[i]; }
			if (elements->m_Max[i] > max[i]) { max[i] = elements->m_Max[i]; }
			midpoints[i] = static_cast<CScalar>(max[i] + min[i]) * static_cast<CScalar>(0.5);
		}
	}

	if((midpoints[0] == 1 && midpoints[1] == 1 && midpoints[2] == 1) || m_RecurseCounter == m_MaxRecurse)
	{
		std::shared_ptr<CBroadContactInfo> leftover = std::make_shared<CBroadContactInfo>();
		for (auto& current : a_Objects)
		{
			leftover->m_Objects.push_back(current->m_Object);
		}
		return;
	}

	if(midpoints[0] > midpoints[1] && midpoints[0] > midpoints[2])
	{
		for (auto& element1 : a_Objects)
		{
			if(static_cast<int>(element1->m_Object->GetTransform().getOrigin().getX()) < midpoints[0])
			{
				left.push_back(element1);
			}
			else { right.push_back(element1); }
		}
	}
	else if (midpoints[1] > midpoints[0] && midpoints[1] > midpoints[2])
	{
		for (auto& element1 : a_Objects)
		{
			if (static_cast<int>(element1->m_Object->GetTransform().getOrigin().getY()) < midpoints[0])
			{
				left.push_back(element1);
			}
			else { right.push_back(element1); }
		}
	}
	else if (midpoints[2] > midpoints[0] && midpoints[2] > midpoints[1])
	{
		for (auto& element1 : a_Objects)
		{
			if (static_cast<int>(element1->m_Object->GetTransform().getOrigin().getZ()) < midpoints[0])
			{
				left.push_back(element1);
			}
			else { right.push_back(element1); }
		}
	}
	else
	{
		for (auto& element1 : a_Objects)
		{
			if (static_cast<int>(element1->m_Object->GetTransform().getOrigin().getX()) < midpoints[0])
			{
				left.push_back(element1);
			}
			else { right.push_back(element1); }
		}
	}

	if(static_cast<int>(left.size() == 2))
	{
		std::shared_ptr<CBroadContactInfo> info = std::make_shared<CBroadContactInfo>();
		info->m_Objects.push_back(left[0]->m_Object);
		info->m_Objects.push_back(left[1]->m_Object);
		m_Contacts.push_back(info);
	}
	if (static_cast<int>(right.size() == 2))
	{
		std::shared_ptr<CBroadContactInfo> info = std::make_shared<CBroadContactInfo>();
		info->m_Objects.push_back(right[0]->m_Object);
		info->m_Objects.push_back(right[1]->m_Object);
		m_Contacts.push_back(info);

	}
	if (static_cast<int>(left.size()) > 2)
	{
		CreateBVH(left);
	}
	if(static_cast<int>(right.size()) > 2)
	{
		CreateBVH(right);
	}
}


void Cinkes::CBVH::CalculateAxisLength()
{
	std::vector<int> todelete;
	int counter = 0;
	for (auto& element : m_AABBs)
	{
		if (element == nullptr) { todelete.push_back(counter); }
		element = CreateAABB(element->m_Object);
		m_X += element->m_Max[0] - element->m_Min[0];
		m_Y += element->m_Max[1] - element->m_Min[1];
		m_Z += element->m_Max[2] - element->m_Min[2];
		
		counter++;
	}
	for (unsigned int i = 0; i < todelete.size();i++)
	{
		if(std::remove(m_AABBs.begin(), m_AABBs.end(), m_AABBs[todelete[i]]) == m_AABBs.end())
		{
			static_assert(true,"Deleting existing object");
		}
	}
}

void Cinkes::CBVH::Update()
{

	CalculateAxisLength();
	CreateBVH(m_AABBs);
	m_RecurseCounter = 0;
}	
