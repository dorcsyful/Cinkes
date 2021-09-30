#pragma once
#include "CCollisionShape.h"
#include "../CinkesMath/CVector3.h"
namespace Cinkes
{

	class CCompoundPartialShape : public CCollisionShape
	{
	public:
		//Subgroup: Constructors {
		CCompoundPartialShape();
		~CCompoundPartialShape() override;
		CCompoundPartialShape(const CCompoundPartialShape& a_Rhs) noexcept;
		CCompoundPartialShape(CCompoundPartialShape&& a_Rhs) noexcept;
		//}

		//Subgroup: Operators {
		CCompoundPartialShape& operator=(CCompoundPartialShape&& a_Rhs) noexcept;
		CCompoundPartialShape& operator=(const CCompoundPartialShape& a_Rhs) noexcept;
		//}

		//Subgroup: Other {
		void SetShape(CCollisionShape* a_Shape, bool a_DeleteAfterUse, const CVector3& a_Position );
		CCollisionShape* GetShape() { return m_Shape; }
		CVector3 GetPosition() { return m_Position; }
		bool ShouldDelete() { return m_DeleteAfterUse; }
		//}

	private:
		CCollisionShape* m_Shape;
		bool m_DeleteAfterUse;
		CVector3 m_Position;
		ESHAPE_TYPE m_Type = ESHAPE_TYPE::SHAPE_COMPOUND_PARTIAL;
	};

}
