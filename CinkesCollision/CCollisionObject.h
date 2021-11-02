#pragma once
#include "../CinkesMath/CTransform.h"
namespace Cinkes
{
	class CCollisionShape;

	class CCollisionObject
	{
	public:
		//Subgroup: Constructors {
		CCollisionObject();
		explicit CCollisionObject(const CTransform& a_Transform, CCollisionShape* a_Shape = nullptr);
		~CCollisionObject();
		CCollisionObject(const CCollisionObject& a_Rhs);
		CCollisionObject(CCollisionObject&& a_Rhs) noexcept; 
		//}

		//Subgroup: Operators {
		CCollisionObject& operator=(CCollisionObject&& a_Rhs) noexcept;
		//}

		//Subgroup: Shapes {
		void SetCollisionShape(CCollisionShape* a_Shape);
		CCollisionShape* GetCollisionShape() const;
		//}

		//Subgroup: Transform {
		void SetTransform(const CTransform& a_Transform);
		CTransform& GetTransform();
		void SetMoved(bool a_Rhs) { m_Moved = a_Rhs; }
		bool GetMoved() { return m_Moved; }
		bool GetMoved() const { return m_Moved; }
		//}

		bool m_AABBDirty = false;

	private:
		CCollisionShape* m_Shape;
		CTransform m_Transform;
		bool m_Moved;

	};

}
