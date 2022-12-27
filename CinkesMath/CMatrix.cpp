#include "CMatrix.h"
#include <cassert>
Cinkes::CMatrix::CMatrix(unsigned a_Rows, unsigned a_Columns)
{
	std::vector<CScalar> temp;
	for (unsigned i = 0; i < a_Columns; i++) {
		temp.push_back(0);
	}
	for (unsigned i = 0; i < a_Rows; i++) {
		m_Values.push_back(temp);
	}
}

Cinkes::CMatrix::CMatrix()
{
}

std::vector<CScalar> Cinkes::CMatrix::operator[](unsigned a_Row) const
{
	assert(a_Row < m_Values.size());
	return m_Values[a_Row];
}

std::vector<CScalar>& Cinkes::CMatrix::operator[](unsigned a_Row)
{
	assert(a_Row < m_Values.size());
	return m_Values[a_Row];
}

Cinkes::CMatrix Cinkes::CMatrix::operator*(const CMatrix& a_Other)
{
	CMatrix values = CMatrix(m_Values.size(), a_Other[0].size());

	for (int i = 0; i < m_Values.size(); i++) {
		for (int j = 0; j < a_Other[0].size(); j++) {
			values.m_Values[i][j] = Dot(m_Values[i], m_Values[j]);
		}
	}

	return values;
}

void Cinkes::CMatrix::Set(std::vector<std::vector<CScalar>> a_New, int a_StartingRow = 0, int a_StartingColumn = 0)
{
	assert(a_StartingRow < m_Values.size());
	assert(a_StartingColumn < m_Values[0].size());

	if (a_StartingRow < 0 || a_StartingColumn < 0) {
		for (int i = 0; i < m_Values.size(); i++) {
			for (int j = 0; j < m_Values[i].size(); j++) {
				m_Values[i][j] = 0;
			}
		}
	}

	for (unsigned i = a_StartingRow; i < a_New.size(); i++) {
		if (i >= m_Values.size() - 1) { break; }

		for (unsigned j = a_StartingColumn; j < a_New[i].size(); j++) {
			if (j >= m_Values[i].size() - 1) { break; }
			m_Values[i][j] = a_New[i - a_StartingRow][j - a_StartingColumn];
		}
	}
}

void Cinkes::CMatrix::Resize(unsigned a_NewRows, unsigned a_NewColumns, bool a_Reset)
{
	std::vector<std::vector<CScalar>> new_matrix;
	if (a_Reset) {
		m_Values.clear();
		std::vector<CScalar> temp;
		for (unsigned i = 0; i < a_NewColumns; i++) {
			temp.push_back(0);
		}
		for (unsigned i = 0; i < a_NewRows; i++) {
			m_Values.push_back(temp);
		}
		
		return;
	}

	std::vector<CScalar> temp;
	for (int i = 0; i < a_NewRows; i++) 
	{
		new_matrix.push_back(temp);

		for (int j = 0; j < a_NewColumns; j++) 
		{
			if(j > m_Values[i].size() -1) { new_matrix[i].push_back(0); }
			else { new_matrix[i].push_back(m_Values[i][j]); }
		}
	}
	m_Values = new_matrix;
}

void Cinkes::CMatrix::SetZero()
{
	for (int i = 0; i < m_Values.size(); i++) {
		for (int j = 0; j < m_Values[i].size(); j++) {
			m_Values[i][j] = 0;
		}
	}
}

void Cinkes::CMatrix::SetIdentity()
{
}

CScalar Cinkes::CMatrix::Dot(std::vector<CScalar> a_Lhs, std::vector<CScalar> a_Rhs)
{
	assert(a_Lhs.size() == a_Rhs.size());
	CScalar value = 0;

	for (int i = 0; i < a_Lhs.size(); i++) {
		value += a_Lhs[i] * a_Rhs[i];
	}

	return value;
}

Cinkes::CMatrix Cinkes::CMatrix::Transpose()
{
	CMatrix matrix = CMatrix(m_Values[0].size(), m_Values.size());

	for (int i = 0; i < m_Values.size(); i++) {
		for (int j = 0; j < m_Values[i].size(); j++) {
			matrix[j][i] = m_Values[i][j];
		}
	}

	return matrix;
}
