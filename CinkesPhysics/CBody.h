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

		CBody(CBody&& a_Body) noexcept {}
		CBody(const CBody& a_Body) {}

		CBody& operator=(CBody&& a_Rhs) noexcept; 
		CBody& operator=(const CBody& a_Rhs);


	protected:
	};
}

