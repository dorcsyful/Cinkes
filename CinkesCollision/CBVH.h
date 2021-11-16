#pragma once
#include <memory>
#include <vector>

#include "CContactInfo.h"

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
		void LongestAxis(int& a_Axis, int& a_Length, const std::vector<std::shared_ptr<CAABB>>& a_Objects);
		void Partition(std::vector<std::shared_ptr<CAABB>>& a_Left, std::vector<std::shared_ptr<CAABB>>& a_Right);
		void CreateBVH(std::vector<std::shared_ptr<CAABB>>& a_Objects);
		void CalculateAxisLength();
		void Update();

		std::vector<std::shared_ptr<CContactInfo>> m_Contacts;
		//TODO: find a way to make this private
		std::vector<std::shared_ptr<CAABB>> m_AABBs;

	private:
		int m_RecurseCounter = 0;
		const int m_MaxRecurse = 10;
		int m_X = 0;
		int m_Y = 0;
		int m_Z = 0;

	};
}
