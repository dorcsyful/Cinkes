#pragma once
#include <memory>
#include <vector>
#include "CBVH.h"
#include "CGJKAlgorithm.h"
#include "../CinkesMath/CScalar.h"
namespace Cinkes
{
	struct CContactInfo;
	class CBVH;
	class CCollisionObject;
	//Group: CCollision
	/*ClassDescription: Main class of CCollision. Collects all objects and runs the collision detection
	*/
	class CCollisionWorld
	{
		public:
		//Subgroup: Constructors {
		CCollisionWorld();
		~CCollisionWorld() = default;
		CCollisionWorld(const CCollisionWorld& a_Rhs);
		CCollisionWorld(CCollisionWorld&& a_Rhs) noexcept;

		//}

		//Subgroup: Operators {
		CCollisionWorld& operator=(CCollisionWorld&& a_Rhs) noexcept;
		CCollisionWorld& operator=(const CCollisionWorld& a_Rhs);
		//}

		//Subgroup: Object handling {
		bool AddObject(const std::shared_ptr<CCollisionObject>& a_Object);
		bool RemoveObject(const std::shared_ptr<CCollisionObject>& a_Object);
		bool RemoveObjectByIndex(int a_Index);
		//}

		//Subgroup: Collision test {
		std::vector<std::shared_ptr<CContactInfo>>& getContacts() { return m_BVH->m_Contacts; }
		void RunCollision(CScalar a_T);
		//}


	private:
		//Subgroup: Class members
		bool m_ShouldUpdate;
		std::vector<std::shared_ptr<CCollisionObject>> m_Objects;
		std::unique_ptr<CBVH> m_BVH;
		std::unique_ptr<CGJKAlgorithm> m_GJK;
		//}
	};

}
