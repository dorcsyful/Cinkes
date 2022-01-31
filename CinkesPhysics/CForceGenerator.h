#pragma once
#include <vector>

#include "../CinkesMath/CScalar.h"

enum class EGENERATOR_TYPE
{
	TYPE_NO_TYPE,
	TYPE_GRAVITY,
	TYPE_SPRING_BASIC
};

namespace Cinkes
{
	class CRigidBody;
	class CBody;

	class CForceGenerator
	{
	public:
		CForceGenerator() = default;
		virtual ~CForceGenerator() = default;

		virtual void UpdateForce(void* a_Body) = 0;
		EGENERATOR_TYPE GetType() const { return m_Type; }
		bool AddObject(void* a_Object);
		bool RemoveObjectByValue(const void* a_Object);
		bool IsInGenerator(const void* a_Object);

		std::vector<void*> m_Objects;


	protected:
		EGENERATOR_TYPE m_Type = EGENERATOR_TYPE::TYPE_NO_TYPE;
	};
}
