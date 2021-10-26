
// ReSharper disable once CppPrecompiledHeaderIsNotIncluded
#include "CCollisionObject.h"

Cinkes::CCollisionObject::CCollisionObject()
{
	m_Shape = nullptr;
	m_Transform = CTransform();
	m_Moved = false;
}

Cinkes::CCollisionObject::CCollisionObject(const CTransform& a_Transform, CCollisionShape* a_Shape)
{
	m_Transform = a_Transform;
	m_Shape = a_Shape;
	m_Moved = false;
}

Cinkes::CCollisionObject::~CCollisionObject()
{
	m_Shape = nullptr;
}

Cinkes::CCollisionObject::CCollisionObject(const CCollisionObject& a_Rhs)
{
	m_Transform = a_Rhs.m_Transform;
	m_Shape = a_Rhs.m_Shape;
	m_Moved = false;
}

Cinkes::CCollisionObject::CCollisionObject(CCollisionObject&& a_Rhs) noexcept 
{
	m_Transform = a_Rhs.m_Transform;
	m_Shape = a_Rhs.m_Shape;
	m_Moved = false;
}


Cinkes::CCollisionObject& Cinkes::CCollisionObject::operator=(CCollisionObject&& a_Rhs) noexcept
{
	if(&a_Rhs == this)
	{
		return *this;
	}
	m_Transform = a_Rhs.m_Transform;
	m_Shape = a_Rhs.m_Shape;
	m_Moved = false;

	return *this;
}

void Cinkes::CCollisionObject::SetCollisionShape(CCollisionShape* a_Shape)
{
	if(m_Shape != nullptr)
	{
		m_Shape = a_Shape;
	}
}

Cinkes::CCollisionShape* Cinkes::CCollisionObject::GetCollisionShape() const
{
	return m_Shape;
}

void Cinkes::CCollisionObject::SetTransform(const CTransform& a_Transform)
{
	m_Transform = a_Transform;
}

Cinkes::CTransform& Cinkes::CCollisionObject::GetTransform()
{
	return m_Transform;
}
