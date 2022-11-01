#pragma once
#include <vector>

#include "CVector3.h"


namespace Cinkes
{
	//Matrix of arbitrary size. For 3x3 matrices use the CMat3x3 class
	class CMatrix
	{
	public:
		CMatrix() = default;
		CMatrix(size_t a_Rows, size_t a_Columns);
		CMatrix(const CMatrix& a_Rhs);
		CMatrix(CMatrix&& a_Rhs) noexcept;
		~CMatrix() = default;
		CMatrix& operator=(CMatrix&& a_Rhs) noexcept;

		//Subgroup: Operators
		bool operator==(const CMatrix& a_Rhs) const;
		bool operator!=(const CMatrix& a_Rhs) const;
		CMatrix& operator=(const CMatrix& a_Rhs);
		CMatrix operator+(const CMatrix& a_Rhs);
		void operator+=(const CMatrix& a_Rhs);
		CMatrix operator+(const CScalar& a_Rhs);
		void operator+=(const CScalar& a_Rhs);
		CMatrix operator-(const CScalar& a_Rhs);
		void operator-=(const CScalar& a_Rhs);
		CMatrix operator-(const CMatrix& a_Rhs);
		void operator-=(const CMatrix& a_Rhs);
		CMatrix operator*(const CMatrix& a_Rhs);
		void operator*=(const CMatrix& a_Rhs);
		CMatrix operator*(const CScalar& a_Rhs);
		void operator*=(const CScalar& a_Rhs);
		std::vector<CScalar> operator[](size_t a_Row) const;
		std::vector<CScalar>& operator[](size_t a_Row);

		//Resizes the matrix. Tries to keep as much existing values as possible. Can be disabled with the last parameter
		void SetSize(size_t a_Rows, size_t a_Columns, bool a_KeepValues = true);
		std::vector<CScalar> GetRow(size_t a_Row);
		std::vector<CScalar> GetRow(size_t a_Row) const;
		//Can be slow. Try to avoid it when working with large matrices
		std::vector<CScalar> GetColumn(size_t a_Column);
		//Can be slow. Try to avoid it when working with large matrices
		std::vector<CScalar> GetColumn(size_t a_Column) const;
		void SetColumn(size_t a_Num, const std::vector<CScalar>& a_Column);
		CMatrix Transpose();
		CMatrix GetInverse();
		CMatrix GetInverse() const { return GetInverse(); }
	private:

		std::vector<std::vector<CScalar>> m_Values;
	};

}

