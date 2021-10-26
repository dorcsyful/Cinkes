#include "CBVH.h"

Cinkes::CBVH::CBVH(const std::vector<std::shared_ptr<CCollisionObject>>& a_Objects)
{
	for (auto& element : a_Objects)
	{
		CreateAABB(element);
	}
}

std::shared_ptr<Cinkes::CAABB> Cinkes::CBVH::CreateAABB(const std::shared_ptr<CCollisionObject>& a_Object)
{
	std::shared_ptr<CAABB> temp = std::make_shared<CAABB>();



	return temp;
}
