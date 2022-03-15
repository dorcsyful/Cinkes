#pragma once
#include <vector>

#include "../CinkesMath/CVector3.h"
namespace Cinkes
{

	class CSimplex
	{
	private:
		std::vector<CVector3> m_Points;
		std::vector<CVector3> m_PointsA;
		std::vector<CVector3> m_PointsB;
		std::vector<CVector3> m_LocalPoints;

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

		CVector3 getPointA(int a_Rhs) { return m_PointsA[a_Rhs]; }
		CVector3 getPointA(int a_Rhs) const { return m_PointsA[a_Rhs]; }
		CVector3 getPointB(int a_Rhs) { return m_PointsB[a_Rhs]; }
		CVector3 getPointB(int a_Rhs) const { return m_PointsB[a_Rhs]; }

		CSimplex& SetAllA(const std::initializer_list<CVector3>& a_Rhs)
		{
			for (auto i = a_Rhs.begin(); i < a_Rhs.end(); i++)
			{
				m_PointsA[std::distance(a_Rhs.begin(), i)] = *i;
			}
			return *this;
		}

		CSimplex& SetAllB(const std::initializer_list<CVector3>& a_Rhs)
		{
			for (auto i = a_Rhs.begin(); i < a_Rhs.end(); i++)
			{
				m_PointsB[std::distance(a_Rhs.begin(), i)] = *i;
			}
			return *this;
		}

		void SetFinishedLocal()
		{
			for(size_t i = 0; i < m_Points.size(); i++)
			{
				m_LocalPoints.push_back(m_PointsA[i] - m_PointsB[i]);
			}
		}

		void Push_Front(const CVector3& a_Vector3)
		{
			m_Points.insert(m_Points.begin(), a_Vector3);
		}

		void Push_FrontA(const CVector3& a_Vector3)
		{
			m_PointsA.insert(m_PointsA.begin(), a_Vector3);
		}

		void Push_FrontB(const CVector3& a_Vector3)
		{
			m_PointsB.insert(m_PointsB.begin(), a_Vector3);
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

