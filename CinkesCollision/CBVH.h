#pragma once
#include <memory>
#include <vector>

namespace Cinkes
{
	class CCollisionObject;

	struct CAABB 
	{
		int m_Min[3] = { 0,0,0 };
		int m_Max[3] = { 0,0,0 };
		std::shared_ptr<CCollisionObject> m_Object;
	};


	class CBVH
	{
	public:
		CBVH(const std::vector<std::shared_ptr<CCollisionObject>>& a_Objects);
		~CBVH() = default;

		std::shared_ptr<CAABB> CreateAABB(const std::shared_ptr<CCollisionObject>& a_Object);
		int LongestAxis();
		void Partition(std::vector<std::shared_ptr<CAABB>>& a_Left, std::vector<std::shared_ptr<CAABB>>& a_Right);

	private:
		std::vector<std::shared_ptr<CAABB>> m_AABBs;
	};
}
