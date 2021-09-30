#include "pch.h"
#include "CCompoundPartialShape.h"

Cinkes::CCompoundPartialShape::CCompoundPartialShape() : m_Shape(nullptr), m_DeleteAfterUse(false),m_Position(CVector3(0,0,0))
{
}

Cinkes::CCompoundPartialShape::~CCompoundPartialShape()
{
	if (m_DeleteAfterUse) { delete m_Shape; }
	m_Shape = nullptr;
}

Cinkes::CCompoundPartialShape::CCompoundPartialShape(const CCompoundPartialShape& a_Rhs) noexcept
{
	m_Shape = a_Rhs.m_Shape;
	m_DeleteAfterUse = a_Rhs.m_DeleteAfterUse;
	m_Position = a_Rhs.m_Position;
	if (this != &a_Rhs) {
		m_Shape = a_Rhs.m_Shape;
		m_DeleteAfterUse = a_Rhs.m_DeleteAfterUse;
		m_Position = a_Rhs.m_Position;
	}
}

Cinkes::CCompoundPartialShape::CCompoundPartialShape(CCompoundPartialShape&& a_Rhs) noexcept
{
	m_Shape = a_Rhs.m_Shape;
	m_DeleteAfterUse = a_Rhs.m_DeleteAfterUse;
	m_Position = a_Rhs.m_Position;
}

Cinkes::CCompoundPartialShape& Cinkes::CCompoundPartialShape::operator=(CCompoundPartialShape&& a_Rhs) noexcept
{
	if (this == &a_Rhs) { return *this; }
	m_Shape = a_Rhs.m_Shape;
	m_Position = a_Rhs.m_Position;
	m_DeleteAfterUse = a_Rhs.m_DeleteAfterUse;

	return *this;
}

Cinkes::CCompoundPartialShape& Cinkes::CCompoundPartialShape::operator=(const CCompoundPartialShape& a_Rhs) noexcept
{
	if (this == &a_Rhs) { return *this; }

	m_Shape = a_Rhs.m_Shape;
	m_Position = a_Rhs.m_Position;
	m_DeleteAfterUse = a_Rhs.m_DeleteAfterUse;

	return *this;
}

void Cinkes::CCompoundPartialShape::SetShape(CCollisionShape* a_Shape, bool a_DeleteAfterUse, const CVector3& a_Position)
{
	m_Shape = a_Shape;
	m_DeleteAfterUse = a_DeleteAfterUse;
	m_Position = a_Position;
}
