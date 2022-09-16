#pragma once
#include <vector>

#include "../CinkesMath/CVector3.h"
namespace Cinkes
{

	class CSimplex
	{
	private:
		std::vector<CVector3> m_Points;

	public:
		CSimplex() { m_Points.reserve(4); }

		CSimplex& operator=(const std::initializer_list<CVector3>& a_Rhs)
		{
			for(auto i = a_Rhs.begin(); i < a_Rhs.end(); i++)
			{
				m_Points[std::distance(a_Rhs.begin(), i)] = *i;
			}
			return *this;
		}

		void Push_Front(const CVector3& a_Vector3)
		{
			m_Points.insert(m_Points.begin(), a_Vector3);
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
		unsigned Size() const { return  static_cast<unsigned>(m_Points.size()); }

	};
}

