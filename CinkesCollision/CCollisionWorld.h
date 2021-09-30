#pragma once
#include <vector>
#include "../CinkesMath/CScalar.h"
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
		CCollisionWorld();
		~CCollisionWorld();
		CCollisionWorld(const CCollisionWorld& a_Rhs);
		CCollisionWorld(CCollisionWorld&& a_Rhs);

		//}

		//Subgroup: Operators {
		CCollisionWorld& operator=(CCollisionWorld&& a_Rhs);
		CCollisionWorld& operator=(const CCollisionWorld& a_Rhs);
		CCollisionObject* operator[](int a_Rhs);
		//}

		//Subgroup: Object handling {
		bool AddObject(CCollisionObject* a_Object);
		bool RemoveObject(CCollisionObject* a_Object);
		//}

		//Subgroup: Collision test {
		void RunCollision(CScalar a_T);
		//}

	private:
		//Subgroup: Class members
		std::vector<CCollisionObject*> m_Objects;
		//}
	};

}
