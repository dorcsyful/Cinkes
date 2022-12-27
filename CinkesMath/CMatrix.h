#pragma once
#include "CScalar.h"
#include <vector>
namespace Cinkes {

	//Class created specifically for collision resolution as it deals with giant matrices.
	//It's very barefoot and will likely stay that way for the forseeable future
	class CMatrix
	{
	public:
		CMatrix(unsigned a_Rows, unsigned a_Columns);
		CMatrix();

		std::vector<CScalar> operator[](unsigned a_Row) const;
		std::vector<CScalar>& operator[](unsigned a_Row);
		CMatrix operator*(const CMatrix& a_Other);

		//Sets an aribtrary amount of values in an arbitrary place, overriding the values already there 
		//If a_StartingRow or a_StartingColumn is < 0 the full thing is overwritten.
		void Set(std::vector<std::vector<CScalar>> a_New, int a_StartingRow, int a_StartingColumn);

		//If a_Reset is true every value will be overwritten to 0, other wise it tries to fit what it can into the new size
		void Resize(unsigned a_NewRows, unsigned a_NewColumns, bool a_Reset = true);
		
		void SetZero();
		void SetIdentity();
		int GetNumRows() { return m_Values.size(); }
		int GetNumColumns() { return m_Values[0].size(); }
		int GetNumAll() { return m_Values.size() * m_Values[0].size(); }

		//Mainly for internal use
		CScalar Dot(std::vector<CScalar> a_Lhs, std::vector<CScalar> a_Rhs);
		CMatrix Transpose();
	private:
		std::vector<std::vector<CScalar>> m_Values;
	};
}