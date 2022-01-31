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

		virtual bool AddGenerator(CForceGenerator* a_Generator);

		unsigned HasForceGenerator(EGENERATOR_TYPE a_Type);
		unsigned HasForceGenerator(CForceGenerator* a_Generator);
		bool RemoveGeneratorByIndex(unsigned a_Index);
		bool RemoveGeneratorByType(EGENERATOR_TYPE a_Type);
		bool RemoveGeneratorByValue(CForceGenerator* a_Generator);
		std::vector<CForceGenerator*>& GetAllGenerators() { return m_ForceGenerators; }

	protected:
		std::vector<CForceGenerator*> m_ForceGenerators;
	};
}

