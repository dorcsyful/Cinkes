#pragma once
#include "../CinkesMath/CVector3.h"
#include "CCollisionShape.h"
#include "CCompoundPartialShape.h"
#include <vector>
namespace Cinkes
{
    class CCompoundShape : CCollisionShape
    {
    public:
		//Subgroup: Constructors {
		CCompoundShape() = default;
    	virtual ~CCompoundShape() override;
    	CCompoundShape(const CCompoundShape& a_Rhs);
		CCompoundShape(CCompoundShape&& a_Rhs) noexcept;
		//}

		//Subgroup: Operators {
		CCompoundShape& operator=(CCompoundShape&& a_Rhs) noexcept;
		CCompoundShape& operator=(const CCompoundShape& a_Rhs);
		std::shared_ptr<CCompoundPartialShape> operator[](int a_Rhs);
		//}

		//Subgroup: Other {
		bool AddShape(const std::shared_ptr<CCompoundPartialShape>& a_Partial);
		int FindShapeIndex(const std::shared_ptr<CCollisionShape>& a_Shape);
		bool RemoveShapeByIndex(int a_Index);
		std::shared_ptr<CCompoundPartialShape> GetShapeAtIndex(int a_Index);
		std::shared_ptr<CCompoundPartialShape> GetShapeAtPosition(const CVector3& a_Position);
		std::vector<std::shared_ptr<CCollisionShape>> GetAllShapesOfType(ESHAPE_TYPE a_Type);
		std::vector<std::shared_ptr<CCollisionShape>> GetAllShapes();
		std::vector<CVector3> GetAllPositions();
    	std::vector<CVector3> SupportPointsForContact(const CVector3& a_Direction, const CTransform& a_Position) override;
		//}

    private:
		std::vector<std::shared_ptr<CCompoundPartialShape>> m_Shapes;
    };
}

