#pragma once
#include <array>
#include "../CinkesMath/CVector3.h"
namespace Cinkes
{

	class CSimplex
	{
	private:
		std::array<Cinkes::CVector3, 4> m_Points;
		unsigned int m_Size;

	public:
		CSimplex() : m_Points(std::array<CVector3,4>()), m_Size(0) {}

		CSimplex& operator=(const std::initializer_list<CVector3>& a_Rhs)
		{
			for(auto i = a_Rhs.begin(); i < a_Rhs.end(); i++)
			{
				m_Points[std::distance(a_Rhs.begin(), i)] = *i;
			}
			m_Size = static_cast<unsigned>(a_Rhs.size());
			return *this;
		}

		void Push_Front(const CVector3& a_Vector3)
		{
			m_Points = { a_Vector3,m_Points[0],m_Points[1],m_Points[2] };
			m_Size = std::min(m_Size + 1, 4u);
		}

		CVector3& operator[](int a_Number) { return m_Points[a_Number]; }
		unsigned Size() { return  m_Size; }
		auto Begin() { return m_Points.begin(); }
		auto End() { return m_Points.end(); }
	};
}

