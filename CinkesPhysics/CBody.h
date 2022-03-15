#pragma once
#include <vector>

#include "CCollisionObject.h"
#include "CForceGenerator.h"
namespace Cinkes
{

	class CBody : public CCollisionObject
	{
	public:
		CBody() { m_Moveable = true; }
		~CBody() override = default;

		CBody(const CBody& a_Rhs) : CCollisionObject(a_Rhs) {
			
		}

		CBody& operator=(CBody&& a_Rhs) noexcept; 
		CBody& operator=(const CBody& a_Rhs);


	protected:
	};
}

