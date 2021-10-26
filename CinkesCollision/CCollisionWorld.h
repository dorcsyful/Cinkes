#pragma once
#include <memory>
#include <vector>

#include "CGJKAlgorithm.h"
#include "../CinkesMath/CScalar.h"
#include "CCollisionAlgorithms/COctree.hpp"
namespace Cinkes
{
	class CCollisionObject;
	//Group: CCollision
	/*ClassDescription: Main class of CCollision. Collects all objects and runs the collision detection
	*/
	class CCollisionWorld
	{
		public:
		//Subgroup: Constructors {
		CCollisionWorld() ;
		~CCollisionWorld();
		CCollisionWorld(const CCollisionWorld& a_Rhs);
		CCollisionWorld(CCollisionWorld&& a_Rhs) noexcept;

		//}

		//Subgroup: Operators {
		CCollisionWorld& operator=(CCollisionWorld&& a_Rhs) noexcept;
		CCollisionWorld& operator=(const CCollisionWorld& a_Rhs);
		//}

		//Subgroup: Object handling {
		bool AddObject(CCollisionObject* a_Object);
		bool RemoveObject(CCollisionObject* a_Object);
		bool RemoveObjectByIndex(int a_Index);
		//}

		//Subgroup: Collision test {
		void RunCollision(CScalar a_T);
		//}

	private:
		//Subgroup: Class members
		std::vector<CCollisionObject*> m_Objects;
		std::unique_ptr<COctree> m_Broadphase;
		std::unique_ptr<CGJKAlgorithm> m_Narrowphase;
		//}
	};

}
