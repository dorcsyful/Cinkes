#pragma once

namespace Cinkes
{
	class CCollisionShape;

	class CCollisionObject
	{
	public:
		//Subgroup: Constructors {
		CCollisionObject();
		~CCollisionObject();
		CCollisionObject(const CCollisionObject& a_Rhs);
		CCollisionObject(CCollisionObject&& a_Rhs);
		//}

		//Subgroup: Operators {
		CCollisionObject& operator=(CCollisionObject&& a_Rhs);
		CCollisionObject& operator=(const CCollisionObject& a_Rhs);
		//}

		//Subgroup: Shapes {
		void SetCollisionShape(CCollisionShape* a_Shape);
		CCollisionShape* GetCollisionShape();
		//}

	private:
		CCollisionShape* m_Shape;
	};

}
