#include "pch.h"
#include "CCompoundPartialShape.h"

Cinkes::CCompoundPartialShape::CCompoundPartialShape() : m_Shape(nullptr),m_Position(CVector3(0,0,0))
{
}

Cinkes::CCompoundPartialShape::~CCompoundPartialShape()
{
	m_Shape = nullptr;
}

Cinkes::CCompoundPartialShape::CCompoundPartialShape(const CCompoundPartialShape& a_Rhs) noexcept
{
	m_Shape = a_Rhs.m_Shape;
	m_Position = a_Rhs.m_Position;
	if (this != &a_Rhs) {
		m_Shape = a_Rhs.m_Shape;
		m_Position = a_Rhs.m_Position;
	}
}

Cinkes::CCompoundPartialShape::CCompoundPartialShape(CCompoundPartialShape&& a_Rhs) noexcept
{
	m_Shape = a_Rhs.m_Shape;
	m_Position = a_Rhs.m_Position;
}

Cinkes::CCompoundPartialShape& Cinkes::CCompoundPartialShape::operator=(CCompoundPartialShape&& a_Rhs) noexcept
{
	if (this == &a_Rhs) { return *this; }
	m_Shape = a_Rhs.m_Shape;
	m_Position = a_Rhs.m_Position;

	return *this;
}

Cinkes::CCompoundPartialShape& Cinkes::CCompoundPartialShape::operator=(const CCompoundPartialShape& a_Rhs) noexcept
{
	if (this == &a_Rhs) { return *this; }

	m_Shape = a_Rhs.m_Shape;
	m_Position = a_Rhs.m_Position;

	return *this;
}

void Cinkes::CCompoundPartialShape::SetShape(std::shared_ptr<CCollisionShape> a_Shape, bool a_DeleteAfterUse, const CVector3& a_Position)
{
	m_Shape = a_Shape;
	m_Position = a_Position;
}
