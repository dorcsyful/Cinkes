#pragma once
#include "../CinkesCollision/CCollisionObject.h"

namespace Cinkes
{
	class CBody : public CCollisionObject
	{
	public:
		CBody() = default;
		~CBody() override = default;
	};
}

