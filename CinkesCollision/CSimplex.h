#pragma once
#include <vector>

#include "../CinkesMath/CVector3.h"
namespace Cinkes
{

	class CSimplex
	{

	public:
		CSimplex() :
			m_Size(0)
		{}

		CSimplex& operator=(std::initializer_list<CVector3> list) {
			for (auto v = list.begin(); v != list.end(); v++) {
				m_Points[std::distance(list.begin(), v)] = *v;
			}
			m_Size = list.size();

			return *this;
		}

		void Push_Front(const CVector3& a_Vector3)
		{
			m_Points.insert(m_Points.begin(), a_Vector3);
			m_Size = m_Points.size();
		}

		bool Erase(const CVector3& a_Vector3)
		{
			if(remove(m_Points.begin(), m_Points.end(), a_Vector3) == m_Points.end())
			{
				return false;
			}
			return true;
		}

		CVector3& operator[](int a_Number) { return m_Points[a_Number]; }
		CVector3 operator[](int a_Number) const { return m_Points[a_Number]; }
		size_t Size() const { return m_Points.size(); }

		std::vector<CVector3> m_Points;
		size_t m_Size;


	};
}

