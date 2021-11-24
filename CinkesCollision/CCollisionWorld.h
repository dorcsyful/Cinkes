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
		std::shared_ptr<CCollisionObject> operator[](int a_Rhs) { return m_Objects[a_Rhs]; }
		//}

		//Subgroup: Object handling {
		bool AddObject(const std::shared_ptr<CCollisionObject>& a_Object);
		bool RemoveObject(const std::shared_ptr<CCollisionObject>& a_Object);
		bool RemoveObjectByIndex(int a_Index);
		unsigned int GetNumberOfObjects() { return m_Objects.size(); }
		std::shared_ptr<CCollisionObject> GetObjectByIndex(int a_Num) { return m_Objects[a_Num]; }
		void Stop() { m_ShouldUpdate = false; }
		void Start() { m_ShouldUpdate = true; }
		bool GetStatus() { return m_ShouldUpdate; }

		//}

		//Subgroup: Collision test {
		std::vector<std::shared_ptr<CContactInfo>>& getContacts() { return m_Contacts; }
		void RunCollision(CScalar a_T);
		//}


	private:
		//Subgroup: Class members
		bool m_ShouldUpdate;
		std::vector<std::shared_ptr<CCollisionObject>> m_Objects;
		std::vector<std::shared_ptr<CContactInfo>> m_Contacts;
		std::unique_ptr<CBVH> m_BVH;
		std::unique_ptr<CGJKAlgorithm> m_GJK;
		//}
	};

}
