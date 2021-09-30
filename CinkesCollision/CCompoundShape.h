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
		CCollisionShape* operator[](int a_Rhs);
		//}

		//Subgroup: Other {
		bool AddShape(CCompoundPartialShape* a_Partial);
		int FindShapeIndex(CCollisionShape* a_Shape);
		bool RemoveShapeByIndex(int a_Index);
		CCompoundPartialShape* GetShapeAtIndex(int a_Index);
		CCompoundPartialShape* GetShapeAtPosition(CVector3 a_Position);
		std::vector<CCollisionShape*> GetAllShapesOfType(ESHAPE_TYPE a_Type);
		std::vector<CCollisionShape*> GetAllShapes();
		std::vector<CVector3> GetAllPositions();
		//}

    private:
		std::vector<CCompoundPartialShape*> m_Shapes;
    };
}

