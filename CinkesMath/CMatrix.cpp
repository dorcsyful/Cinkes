#include "CMatrix.h"

#include <cassert>

#include "CUtils.h"

Cinkes::CMatrix::CMatrix(size_t a_Rows, size_t a_Columns)
{
	for(size_t i = 0; i < a_Rows; i++)
	{
		std::vector<CScalar> temp = std::vector<CScalar>(a_Columns);
		temp[static_cast<size_t>(i) * a_Columns] = 1;
		for(size_t j = 0; j < a_Columns; j++)
		{
			if (j != i * a_Columns) { temp[j] = 0; }
		}
		m_Values.push_back(temp);
	}
}

Cinkes::CMatrix::CMatrix(const CMatrix& a_Rhs)
{
	m_Values = a_Rhs.m_Values;
}

Cinkes::CMatrix::CMatrix(CMatrix&& a_Rhs) noexcept
{
	m_Values = a_Rhs.m_Values;
}

Cinkes::CMatrix& Cinkes::CMatrix::operator=(CMatrix&& a_Rhs) noexcept
{
	m_Values = a_Rhs.m_Values;
	return *this;
}

bool Cinkes::CMatrix::operator==(const CMatrix& a_Rhs) const
{
	for(size_t i = 0; i < a_Rhs.m_Values.size(); i++)
	{
		for(size_t j = 0; j < a_Rhs.m_Values[i].size(); j++)
		{
			if(CUtils::Abs(m_Values[i][j] - a_Rhs[i][j]) > CEPSILON)
			{
				return false;
			}
		}
	}
	return true;
}

bool Cinkes::CMatrix::operator!=(const CMatrix& a_Rhs) const
{
	for (size_t i = 0; i < a_Rhs.m_Values.size(); i++)
	{
		for (size_t j = 0; j < a_Rhs.m_Values[i].size(); j++)
		{
			if (CUtils::Abs(m_Values[i][j] - a_Rhs[i][j]) < CEPSILON)
			{
				return false;
			}
		}
	}
	return true;
}

Cinkes::CMatrix& Cinkes::CMatrix::operator=(const CMatrix& a_Rhs)
= default;

Cinkes::CMatrix Cinkes::CMatrix::operator+(const CMatrix& a_Rhs)
{
	assert(a_Rhs.m_Values.size() == m_Values.size());
	assert(a_Rhs.m_Values[0].size() == m_Values[0].size());
	CMatrix added = CMatrix(m_Values.size(),m_Values[0].size());
	for(size_t i = 0; i < m_Values.size(); i++)
	{
		for(size_t j = 0; j < m_Values[0].size(); j++)
		{
			added[i][j] = m_Values[i][j] + a_Rhs.m_Values[i][j];
		}
	}
	return added;
}

void Cinkes::CMatrix::operator+=(const CMatrix& a_Rhs)
{

	assert(a_Rhs.m_Values.size() == m_Values.size());
	assert(a_Rhs.m_Values[0].size() == m_Values[0].size());
	for (size_t i = 0; i < m_Values.size(); i++)
	{
		for (size_t j = 0; j < m_Values[0].size(); j++)
		{
			m_Values[i][j] = m_Values[i][j] + a_Rhs.m_Values[i][j];
		}
	}
}

Cinkes::CMatrix Cinkes::CMatrix::operator+(const CScalar& a_Rhs)
{
	CMatrix added = CMatrix(m_Values.size(), m_Values[0].size());
	for (size_t i = 0; i < m_Values.size(); i++)
	{
		for (size_t j = 0; j < m_Values[0].size(); j++)
		{
			added.m_Values[i][j] = m_Values[i][j] + a_Rhs;
		}
	}
	return added;
}

void Cinkes::CMatrix::operator+=(const CScalar& a_Rhs)
{
	for (auto& value : m_Values)
	{
		for (size_t j = 0; j < m_Values[0].size(); j++)
		{
			value[j] = value[j] + a_Rhs;
		}
	}
}

Cinkes::CMatrix Cinkes::CMatrix::operator-(const CScalar& a_Rhs)
{
	CMatrix subbed = CMatrix(m_Values.size(), m_Values[0].size());
	for (size_t i = 0; i < m_Values.size(); i++)
	{
		for (size_t j = 0; j < m_Values[0].size(); j++)
		{
			subbed.m_Values[i][j] = m_Values[i][j] - a_Rhs;
		}
	}
	return subbed;
}

void Cinkes::CMatrix::operator-=(const CScalar& a_Rhs)
{
	for (auto& value : m_Values)
	{
		for (size_t j = 0; j < m_Values[0].size(); j++)
		{
			value[j] = value[j] - a_Rhs;
		}
	}
}

Cinkes::CMatrix Cinkes::CMatrix::operator-(const CMatrix& a_Rhs)
{
	assert(a_Rhs.m_Values.size() == m_Values.size());
	assert(a_Rhs.m_Values[0].size() == m_Values[0].size());
	CMatrix subbed = CMatrix(m_Values.size(), m_Values[0].size());
	for (size_t i = 0; i < m_Values.size(); i++)
	{
		for (size_t j = 0; j < m_Values[0].size(); j++)
		{
			subbed[i][j] = m_Values[i][j] - a_Rhs.m_Values[i][j];
		}
	}
	return subbed;
}

void Cinkes::CMatrix::operator-=(const CMatrix& a_Rhs)
{
	assert(a_Rhs.m_Values.size() == m_Values.size());
	assert(a_Rhs.m_Values[0].size() == m_Values[0].size());
	for (size_t i = 0; i < m_Values.size(); i++)
	{
		for (size_t j = 0; j < m_Values[0].size(); j++)
		{
			m_Values[i][j] = m_Values[i][j] - a_Rhs.m_Values[i][j];
		}
	}
}

Cinkes::CMatrix Cinkes::CMatrix::operator*(const CMatrix& a_Rhs)
{
	assert(m_Values[0].size() == a_Rhs.m_Values.size());

	CMatrix result = CMatrix(m_Values.size(), a_Rhs.m_Values[0].size());

	for(size_t n = 0; n < m_Values.size(); n++)
	{
		for(size_t j = 0; j < a_Rhs.m_Values[0].size(); j++)
		{
			CScalar sum = 0;
			for(size_t k = 0; k < a_Rhs.m_Values[0].size(); k++)
			{
				sum += m_Values[j][k] * a_Rhs.m_Values[k][j];
			}
			result[n][j] = sum;
		}
	}

	return result;
}

void Cinkes::CMatrix::operator*=(const CMatrix& a_Rhs)
{
	assert(m_Values[0].size() == a_Rhs.m_Values.size());

	CMatrix result = CMatrix(m_Values.size(), a_Rhs.m_Values[0].size());

	for (size_t n = 0; n < m_Values.size(); n++)
	{
		for (size_t j = 0; j < a_Rhs.m_Values[0].size(); j++)
		{
			CScalar sum = 0;
			for (size_t k = 0; k < a_Rhs.m_Values[0].size(); k++)
			{
				sum += m_Values[j][k] * a_Rhs.m_Values[k][j];
			}
			result[n][j] = sum;
		}
	}

	m_Values = result.m_Values;
}

Cinkes::CMatrix Cinkes::CMatrix::operator*(const CScalar& a_Rhs)
{
	CMatrix multiplied = CMatrix(m_Values.size(), m_Values[0].size());
	for (size_t i = 0; i < m_Values.size(); i++)
	{
		for (size_t j = 0; j < m_Values[0].size(); j++)
		{
			multiplied.m_Values[i][j] = m_Values[i][j] * a_Rhs;
		}
	}
	return multiplied;
}

void Cinkes::CMatrix::operator*=(const CScalar& a_Rhs)
{
	for (auto& value : m_Values)
	{
		for (size_t j = 0; j < m_Values[0].size(); j++)
		{
			value[j] = value[j] * a_Rhs;
		}
	}
}

std::vector<CScalar> Cinkes::CMatrix::operator[](size_t a_Row) const
{
	return m_Values[a_Row];
}

std::vector<CScalar>& Cinkes::CMatrix::operator[](size_t a_Row)
{
	return m_Values[a_Row];
}

void Cinkes::CMatrix::SetSize(size_t a_Rows, size_t a_Columns, bool a_KeepValues)
{
	if(a_KeepValues)
	{
		std::vector<std::vector<CScalar>> new_values;
		for(size_t i = 0; i < a_Rows; i++)
		{
			std::vector<CScalar> temp;
			for(size_t j = 0; j < a_Columns; j++)
			{
				if(m_Values.size() <= a_Rows && m_Values[0].size() <= a_Columns)
				{
					temp.push_back(m_Values[i][j]);
				}
			}
			new_values.push_back(temp);
		}
	}
	else
	{
		*this = CMatrix(a_Rows, a_Columns);
	}
}

std::vector<CScalar> Cinkes::CMatrix::GetRow(size_t a_Row)
{
	return m_Values[a_Row];
}

std::vector<CScalar> Cinkes::CMatrix::GetRow(size_t a_Row) const
{
	return m_Values[a_Row];
}

std::vector<CScalar> Cinkes::CMatrix::GetColumn(size_t a_Column)
{
	std::vector<CScalar> column;
	for (auto& value : m_Values)
	{
		column.push_back(value[a_Column]);
	}
	return column;
}

std::vector<CScalar> Cinkes::CMatrix::GetColumn(size_t a_Column) const
{
	std::vector<CScalar> column;
	for (const auto& value : m_Values)
	{
		column.push_back(value[a_Column]);
	}
	return column;
}

void Cinkes::CMatrix::SetColumn(size_t a_Num, const std::vector<CScalar>& a_Column)
{
	for(size_t i = 0; i < m_Values.size(); i++)
	{
		m_Values[i][a_Num] = a_Column[i];
	}
}

Cinkes::CMatrix Cinkes::CMatrix::Transpose()
{
	CMatrix new_matrix = CMatrix(m_Values[0].size(), m_Values.size());
	for(size_t i = 0; i < m_Values[0].size(); i++)
	{
		new_matrix[i] = GetColumn(i);
	}
	return new_matrix;
}

Cinkes::CMatrix Cinkes::CMatrix::GetInverse()
{
	//TODO Finish this
	assert(m_Values.size() == m_Values[0].size());
	CMatrix new_matrix;
	return new_matrix;
}
