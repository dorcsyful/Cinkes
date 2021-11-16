#pragma once
#include <memory>
#include <vector>

#include "CGJKAlgorithm.h"
#include "../CinkesMath/CScalar.h"
namespace Cinkes
{
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
		~CCollisionWorld();
		CCollisionWorld(const CCollisionWorld& a_Rhs);
		CCollisionWorld(CCollisionWorld&& a_Rhs) noexcept;

		//}

		//Subgroup: Operators {
		CCollisionWorld& operator=(CCollisionWorld&& a_Rhs) noexcept;
		CCollisionWorld& operator=(const CCollisionWorld& a_Rhs);
		bool operator==(CCollisionWorld* a_Rhs) { return true; }
		//}

		//Subgroup: Object handling {
		bool AddObject(const std::shared_ptr<CCollisionObject>& a_Object);
		bool RemoveObject(const std::shared_ptr<CCollisionObject>& a_Object);
		bool RemoveObjectByIndex(int a_Index);
		//}

		//Subgroup: Collision test {
		void RunCollision(CScalar a_T);
		//}
		std::unique_ptr<CBVH> m_BVH;

	private:
		//Subgroup: Class members
		bool m_ShouldUpdate;
		std::vector<std::shared_ptr<CCollisionObject>> m_Objects;
		//}
	};

}
