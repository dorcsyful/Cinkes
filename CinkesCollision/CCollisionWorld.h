#pragma once
#include <memory>
#include <vector>
#include "CBVH.h"
#include "CGJKAlgorithm.h"
#include "CEPA.h"
#include "CScalar.h"
#include "CContactPointCalculator.h"

namespace Cinkes
{
	class CRigidBody;
	class CContactPointCalculator;
	struct CContactInfo;
	class CBVH;
	class CCollisionObject;
	//Group: CCollision
	/*ClassDescription: Main class of CCollision. Collects all objects and runs the collision detection. 
	*/
	class CCollisionWorld
	{
		public:
		//Subgroup: Constructors {
		CCollisionWorld();
		~CCollisionWorld() = default;
		CCollisionWorld(const CCollisionWorld& a_Rhs) = delete;
		CCollisionWorld(CCollisionWorld&& a_Rhs) noexcept = default;

		//}

		//Subgroup: Operators {
		CCollisionWorld& operator=(CCollisionWorld&& a_Rhs) noexcept = default;
		CCollisionWorld& operator=(const CCollisionWorld& a_Rhs);
		std::shared_ptr<CCollisionObject> operator[](int a_Rhs) { return m_Objects[a_Rhs]; }
		//}

		//Subgroup: Object handling {
		bool AddObject(const std::shared_ptr<CCollisionObject>& a_Object);
		bool RemoveObject(const std::shared_ptr<CCollisionObject>& a_Object);
		bool RemoveObjectByIndex(int a_Index);
		size_t GetNumberOfObjects() const { return m_Objects.size(); }
		std::shared_ptr<CCollisionObject> GetObjectByIndex(int a_Num) { return m_Objects[a_Num]; }
		void Stop() { m_ShouldUpdate = false; }
		void Start() { m_ShouldUpdate = true; }
		bool GetStatus() const { return m_ShouldUpdate; }

		//}

		//Subgroup: Collision test {
		void getContacts(std::vector<std::shared_ptr<CContactInfo>>& a_Narrow, std::vector<std::shared_ptr<CBroadContactInfo>>& a_Broad) const
		{
			a_Narrow = m_Contacts;
			a_Broad = m_BVH->m_Contacts;
		}
		void RunCollision(CScalar a_T);
		//}


	private:
		//Subgroup: Class members
		bool m_ShouldUpdate;
		std::vector<std::shared_ptr<CCollisionObject>> m_Objects;
		std::vector<std::shared_ptr<CRigidBody>> m_RigidBodies;
		std::vector<std::shared_ptr<CContactInfo>> m_Contacts;
		std::unique_ptr<CBVH> m_BVH;
		std::unique_ptr<CGJKAlgorithm> m_GJK;
		std::unique_ptr<CEPA> m_CEPA;
		std::unique_ptr<CContactPointCalculator> m_ContactPointCalculator;
		//}
	};

}
