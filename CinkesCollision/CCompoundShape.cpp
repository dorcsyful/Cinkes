#include "pch.h"
#include "CCompoundShape.h"

Cinkes::CCompoundShape::~CCompoundShape()
{
	for (const auto element : m_Shapes)
	{
		delete element;
	}
}

Cinkes::CCompoundShape::CCompoundShape(const CCompoundShape& a_Rhs)
{
	m_Shapes = a_Rhs.m_Shapes;
}

Cinkes::CCompoundShape::CCompoundShape(CCompoundShape&& a_Rhs) noexcept
{
	m_Shapes = a_Rhs.m_Shapes;
}

Cinkes::CCompoundShape& Cinkes::CCompoundShape::operator=(CCompoundShape&& a_Rhs) noexcept
{
	m_Shapes = a_Rhs.m_Shapes;
	return *this;
}

Cinkes::CCompoundShape& Cinkes::CCompoundShape::operator=(const CCompoundShape& a_Rhs)
{
	m_Shapes = a_Rhs.m_Shapes;
	return  *this;
}

Cinkes::CCollisionShape* Cinkes::CCompoundShape::operator[](int a_Rhs)
{
	return m_Shapes[a_Rhs];
}

bool Cinkes::CCompoundShape::AddShape(CCompoundPartialShape* a_Partial)
{
	m_Shapes.push_back(a_Partial);
	return true;
}

int Cinkes::CCompoundShape::FindShapeIndex(CCollisionShape* a_Shape)
{
	int counter = 0;
	for (auto element : m_Shapes)
	{
		if(element == a_Shape)
		{
			return counter + 1;
		}
		counter++;
	}
	return counter;
}

bool Cinkes::CCompoundShape::RemoveShapeByIndex(int a_Index)
{
	m_Shapes.erase(m_Shapes.begin() + a_Index);
	return true;
}

Cinkes::CCompoundPartialShape* Cinkes::CCompoundShape::GetShapeAtIndex(int a_Index)
{
	return m_Shapes[a_Index];
}

Cinkes::CCompoundPartialShape* Cinkes::CCompoundShape::GetShapeAtPosition(CVector3 a_Position)
{
	for (const auto element : m_Shapes)
	{
		if((element->GetPosition() - a_Position).Length() < CScalar(0.001))
		{
			return element;
		}
	}
	return nullptr;
}

std::vector<Cinkes::CCollisionShape*> Cinkes::CCompoundShape::GetAllShapesOfType(ESHAPE_TYPE a_Type)
{
	std::vector<Cinkes::CCollisionShape*> shapes;
	for (auto shape : m_Shapes)
	{
		if(shape->GetShape()->GetType() == a_Type)
		{
			shapes.push_back(shape->GetShape());
		}
	}
	return shapes;
}

std::vector<Cinkes::CCollisionShape*> Cinkes::CCompoundShape::GetAllShapes()
{
	std::vector<Cinkes::CCollisionShape*> shapes;
	for (const auto shape : m_Shapes)
	{
		bool isFound = false;
		for (const auto element : m_Shapes)
		{
			if(element->GetShape() == shape->GetShape())
			{
				isFound = true;
			}
		}
		if (!isFound) { shapes.push_back(shape->GetShape()); }
	}

	return shapes;
}

std::vector<Cinkes::CVector3> Cinkes::CCompoundShape::GetAllPositions()
{
	std::vector<Cinkes::CVector3> positions;
	for (const auto shape : m_Shapes)
	{
		bool isFound = false;
		if (!isFound) { positions.push_back(shape->GetPosition()); }
	}

	return positions;
}
