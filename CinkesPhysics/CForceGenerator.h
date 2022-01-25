#pragma once
#include "../CinkesMath/CScalar.h"

enum class EGENERATOR_TYPE
{
	TYPE_NO_TYPE,
	TYPE_GRAVITY
};

namespace Cinkes
{
	class CBody;

	class CForceGenerator
	{
	public:
		CForceGenerator() = default;
		virtual ~CForceGenerator() = default;

		virtual void UpdateForce(CBody* a_Body, CScalar a_T) = 0;
		EGENERATOR_TYPE GetType() const { return m_Type; }

	protected:
		EGENERATOR_TYPE m_Type = EGENERATOR_TYPE::TYPE_NO_TYPE;
	};
}
