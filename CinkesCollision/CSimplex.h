#pragma once
#include <vector>

#include "../CinkesMath/CVector3.h"
namespace Cinkes
{

	class CSimplex
	{
	private:
		std::vector<CVector3> m_Points;
		unsigned int m_Size;

	public:
		CSimplex()
			: m_Points({ CVector3(), CVector3(), CVector3(), CVector3()})
			, m_Size(0)
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
				m_Points = { a_Vector3, m_Points[0], m_Points[1], m_Points[2] };
				m_Size = std::min(m_Size + 1, 4u);
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
		unsigned Size() const { return m_Size; }

		auto begin() const { return m_Points.begin(); }
		auto end()   const { return m_Points.end() - (4 - m_Size); }

	};
}

