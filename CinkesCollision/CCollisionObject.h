#pragma once
#include <memory>

#include "CTransform.h"
namespace Cinkes
{
	enum class EOBJECT_TYPE
	{
		TYPE_COLLISION,
		TYPE_RIGID,
		TYPE_SOFT
	};

	struct CContactInfo;
	class CCollisionShape;

	class CCollisionObject
	{
	public:
		//Subgroup: Constructors {
		CCollisionObject();
		explicit CCollisionObject(const CTransform& a_Transform, std::shared_ptr<CCollisionShape> a_Shape = nullptr);
		virtual ~CCollisionObject();
		CCollisionObject(const CCollisionObject& a_Rhs);
		CCollisionObject(CCollisionObject&& a_Rhs) noexcept; 
		//}

		//Subgroup: Operators {
		CCollisionObject& operator=(CCollisionObject&& a_Rhs) noexcept;
		CCollisionObject& operator=(const CCollisionObject& a_Rhs);

		//}

		//Subgroup: Shapes {
		void SetCollisionShape(const std::shared_ptr<CCollisionShape>& a_Shape);
		std::shared_ptr<CCollisionShape> GetCollisionShape() const;
		//}

		//Subgroup: Transform {
		void SetTransform(const CTransform& a_Transform);
		CTransform& GetTransform();
		CTransform GetTransform() const;
		void SetMoveable(bool a_Rhs) { m_Moveable = a_Rhs; }
		bool GetMoveable() { return m_Moveable; }
		bool GetMoveable() const { return m_Moveable; }
		void SetHasContact(CContactInfo* a_Rhs) { m_HasContact = a_Rhs; }
		bool GetHasContact() { return m_HasContact; }
		bool GetHasContact() const { return m_HasContact; }
		EOBJECT_TYPE GetType() const { return m_Type; }
		EOBJECT_TYPE GetType() { return m_Type; }
		//}

		bool m_AABBDirty = false;
		bool m_InRemoveQueue = false;

	protected:
		CContactInfo* m_HasContact;
		std::shared_ptr<CCollisionShape> m_Shape;
		CTransform m_Transform;
		bool m_Moveable;
		EOBJECT_TYPE m_Type;
	};

}
