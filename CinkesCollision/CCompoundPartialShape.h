#pragma once
#include <memory>

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
		void SetShape(std::shared_ptr<CCollisionShape> a_Shape, bool a_DeleteAfterUse, const CVector3& a_Position );
		std::shared_ptr<CCollisionShape> GetShape() { return m_Shape; }
		CVector3 GetPosition() { return m_Position; }
		//}

	private:
		std::shared_ptr<CCollisionShape> m_Shape;
		CVector3 m_Position;
		ESHAPE_TYPE m_Type = ESHAPE_TYPE::SHAPE_COMPOUND_PARTIAL;
	};

}
