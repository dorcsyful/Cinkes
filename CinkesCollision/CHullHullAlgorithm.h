#pragma once
#include "CContactInfo.h"
namespace Cinkes
{
	class CHullHullAlgorithm
	{
	public:
		CHullHullAlgorithm() = default;
		~CHullHullAlgorithm() = default;

		CHullHullAlgorithm(const CHullHullAlgorithm& a_Rhs) = delete;
		CHullHullAlgorithm(CHullHullAlgorithm&& a_Rhs) noexcept = delete;
		//}

		//Subgroup: Operators {
		CHullHullAlgorithm& operator=(CHullHullAlgorithm&& a_Rhs) noexcept = delete;
		CHullHullAlgorithm& operator=(const CHullHullAlgorithm& a_Rhs) noexcept = delete;
		bool Exists(const CContactInfo& a_Info){}
		void AddContact(CContactInfo& a_Info) {
			assert(std::find(m_PersistentContact.begin(), m_PersistentContact.end(), a_Info) != m_PersistentContact.end(), 
						"Contact already exists");
			m_PersistentContact.push_back(a_Info);
		}
		void RemoveContactByIndex(int a_Index) {
			m_PersistentContact.erase(std::find(m_PersistentContact.begin(), m_PersistentContact.end(), m_PersistentContact[a_Index]));
		}
		void RemoveContactByReference(CContactInfo& a_Info) {
			m_PersistentContact.erase(std::find(m_PersistentContact.begin(), m_PersistentContact.end(), a_Info));

		}
	private:
		std::vector<CContactInfo&> m_PersistentContact;
	};
}
