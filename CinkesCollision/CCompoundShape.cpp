#include "pch.h"
#include "CCompoundShape.h"

Cinkes::CCompoundShape::~CCompoundShape()
{

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

std::shared_ptr<Cinkes::CCompoundPartialShape> Cinkes::CCompoundShape::operator[](int a_Rhs)
{
	return m_Shapes[a_Rhs];
}

bool Cinkes::CCompoundShape::AddShape(const std::shared_ptr<CCompoundPartialShape>& a_Partial)
{
	m_Shapes.push_back(a_Partial);
	return true;
}

int Cinkes::CCompoundShape::FindShapeIndex(const std::shared_ptr<CCollisionShape>& a_Shape)
{
	int counter = 0;
	for (auto& element : m_Shapes)
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

std::shared_ptr<Cinkes::CCompoundPartialShape> Cinkes::CCompoundShape::GetShapeAtIndex(int a_Index)
{
	return m_Shapes[a_Index];
}

std::shared_ptr<Cinkes::CCompoundPartialShape> Cinkes::CCompoundShape::GetShapeAtPosition(const CVector3& a_Position)
{
	for (const auto& element : m_Shapes)
	{
		if((element->GetPosition() - a_Position).Length() < static_cast<float>(0.001))
		{
			return element;
		}
	}
	return nullptr;
}

std::vector<std::shared_ptr<Cinkes::CCollisionShape>> Cinkes::CCompoundShape::GetAllShapesOfType(ESHAPE_TYPE a_Type)
{
	std::vector<std::shared_ptr<Cinkes::CCollisionShape>> shapes;
	for (auto& shape : m_Shapes)
	{
		if(shape->GetShape()->GetType() == a_Type)
		{
			shapes.push_back(shape->GetShape());
		}
	}
	return shapes;
}

std::vector<std::shared_ptr<Cinkes::CCollisionShape>> Cinkes::CCompoundShape::GetAllShapes()
{
	std::vector<std::shared_ptr<CCollisionShape>> shapes;
	for (const auto& shape : m_Shapes)
	{
		bool isFound = false;
		for (const auto& element : m_Shapes)
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
	for (const auto& shape : m_Shapes)
	{
		bool isFound = false;
		if (!isFound) { positions.push_back(shape->GetPosition()); }
	}

	return positions;
}

std::vector<Cinkes::CVector3> Cinkes::CCompoundShape::SupportPointsForContact(const CVector3& a_Direction, const CVector3& a_Position)
{
	return std::vector<CVector3>();
}
