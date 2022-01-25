#pragma once
#include <memory>
#include <vector>

#include "CForceGenerator.h"
namespace Cinkes
{
	class CForceGeneratorRegistry
	{
	public:
		CForceGeneratorRegistry()  {
			//m_ForceGenerators.push_back(std::make_shared<CGravityGenerator>());
		}
		~CForceGeneratorRegistry() {
			for (int i = static_cast<int>(m_ForceGenerators.size()) - 1; i >= 0; i--)
			{
				RemoveGeneratorByIndex(i);
			}
		}
		CForceGeneratorRegistry(CForceGeneratorRegistry&& a_Rhs) = delete;
		CForceGeneratorRegistry(const CForceGeneratorRegistry& a_Rhs) = delete;
		CForceGeneratorRegistry& operator=(CForceGeneratorRegistry&& a_Rhs) = delete;
		CForceGeneratorRegistry& operator=(const CForceGeneratorRegistry& a_Rhs) = delete;

		bool CreateForceGenerator(EGENERATOR_TYPE a_Type, bool a_AddToAll) { return false; }
		bool AddForceGenerator(const std::shared_ptr<CForceGenerator>& a_Generator, bool a_AddToAll);
		bool RemoveGeneratorByIndex(unsigned a_Index);
		bool RemoveByType(EGENERATOR_TYPE a_Type);
		bool RemoveByValue(CForceGenerator* a_Generator);
		CForceGenerator* GetGeneratorByType(EGENERATOR_TYPE a_Type);

	private:
		std::vector<std::shared_ptr<CForceGenerator>> m_ForceGenerators;
	};
}

