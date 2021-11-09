#include "CQuaternion.h"
#include "CMat3x3.h"

#include "CUtils.h"

using namespace Cinkes;

CMat3x3::CMat3x3()
{
	m_Rows[0] = CVector3(1, 0, 0);
	m_Rows[1] = CVector3(0, 1, 0);
	m_Rows[2] = CVector3(0, 0, 1);
}

CMat3x3::CMat3x3(const CVector3& a_Row1, const CVector3& a_Row2, const CVector3& a_Row3)
{
	m_Rows[0] = a_Row1;
	m_Rows[1] = a_Row2;
	m_Rows[2] = a_Row3;
}

CMat3x3::CMat3x3(CScalar a_00, CScalar a_01, CScalar a_02, CScalar a_10, CScalar a_11, CScalar a_12, CScalar a_20, CScalar a_21, CScalar a_22)
{
	m_Rows[0] = CVector3(a_00, a_01, a_02);
	m_Rows[1] = CVector3(a_10, a_11, a_12);
	m_Rows[2] = CVector3(a_20, a_21, a_22);
}


CMat3x3::CMat3x3(const CMat3x3& a_Copy)
{
	m_Rows[0] = a_Copy[0];
	m_Rows[1] = a_Copy[1];
	m_Rows[2] = a_Copy[2];
}

bool CMat3x3::operator==(const CMat3x3& a_Rhs) const
{
	return (a_Rhs[0] == m_Rows[0]) && (a_Rhs[1] == m_Rows[1]) && (a_Rhs[2] == m_Rows[2]);
}

bool CMat3x3::operator!=(const CMat3x3& a_Rhs) const
{
	return (a_Rhs[0] != m_Rows[0]) || (a_Rhs[1] != m_Rows[1]) || (a_Rhs[2] != m_Rows[2]);

}

CMat3x3& Cinkes::CMat3x3::operator=(const CMat3x3& a_Rhs)
{
	if(this == &a_Rhs)
	{
		return *this;
	}

	m_Rows[0] = a_Rhs[0];
	m_Rows[1] = a_Rhs[1];
	m_Rows[2] = a_Rhs[2];

	return *this;
}

Cinkes::CMat3x3 Cinkes::CMat3x3::operator+(const CMat3x3& a_Rhs)
{
	CMat3x3 matrix;
	matrix[0] = m_Rows[0] + a_Rhs[0];
	matrix[1] = m_Rows[1] + a_Rhs[1];
	matrix[2] = m_Rows[2] + a_Rhs[2];

	return matrix;
}

void Cinkes::CMat3x3::operator+=(const CMat3x3& a_Rhs)
{
	m_Rows[0] += a_Rhs[0];
	m_Rows[1] += a_Rhs[1];
	m_Rows[2] += a_Rhs[2];
}

CMat3x3 CMat3x3::operator+(const CScalar& a_Rhs)
{
	CMat3x3 returnMatrix = CMat3x3();
	returnMatrix[0] = m_Rows[0] + a_Rhs;
	returnMatrix[1] = m_Rows[1] + a_Rhs;
	returnMatrix[2] = m_Rows[2] + a_Rhs;

	return returnMatrix;
}

void CMat3x3::operator+=(const CScalar& a_Rhs)
{
	m_Rows[0] += a_Rhs;
	m_Rows[1] += a_Rhs;
	m_Rows[2] += a_Rhs;
}

CMat3x3 Cinkes::CMat3x3::operator-(const CScalar& a_Rhs)
{
	CMat3x3 returnMatrix;
	returnMatrix[0] = m_Rows[0] - a_Rhs;
	returnMatrix[1] = m_Rows[1] - a_Rhs;
	returnMatrix[2] = m_Rows[2] - a_Rhs;

	return returnMatrix;
}

void Cinkes::CMat3x3::operator-=(const CScalar& a_Rhs)
{
	m_Rows[0] -= a_Rhs;
	m_Rows[1] -= a_Rhs;
	m_Rows[2] -= a_Rhs;
}

Cinkes::CMat3x3 Cinkes::CMat3x3::operator-(const CMat3x3& a_Rhs)
{
	CMat3x3 matrix;
	matrix[0] = m_Rows[0] - a_Rhs[0];
	matrix[1] = m_Rows[1] - a_Rhs[1];
	matrix[2] = m_Rows[2] - a_Rhs[2];

	return matrix;
}

void Cinkes::CMat3x3::operator-=(const CMat3x3& a_Rhs)
{
	m_Rows[0] -= a_Rhs[0];
	m_Rows[1] -= a_Rhs[1];
	m_Rows[2] -= a_Rhs[2];
}

Cinkes::CMat3x3 Cinkes::CMat3x3::operator*(const CMat3x3& a_Rhs)
{
	CMat3x3 matrix;
	CMat3x3 other = a_Rhs;
	CVector3 column1 = other.getColumn(0);
	CVector3 column2 = other.getColumn(1);
	CVector3 column3 = other.getColumn(2);
	matrix[0][0] = m_Rows[0][0] * column1[0] + m_Rows[0][1] * column1[1] + m_Rows[0][2] * column1[2];
	matrix[0][1] = m_Rows[0][0] * column2[0] + m_Rows[0][1] * column2[1] + m_Rows[0][2] * column2[2];
	matrix[0][2] = m_Rows[0][0] * column3[0] + m_Rows[0][1] * column3[1] + m_Rows[0][2] * column3[2];

	matrix[1][0] = m_Rows[1][0] * column1[0] + m_Rows[1][1] * column1[1] + m_Rows[1][2] * column1[2];
	matrix[1][1] = m_Rows[1][0] * column2[0] + m_Rows[1][1] * column2[1] + m_Rows[1][2] * column2[2];
	matrix[1][2] = m_Rows[1][0] * column3[0] + m_Rows[1][1] * column3[1] + m_Rows[1][2] * column3[2];

	matrix[2][0] = m_Rows[2][0] * column1[0] + m_Rows[2][1] * column1[1] + m_Rows[2][2] * column1[2];
	matrix[2][1] = m_Rows[2][0] * column2[0] + m_Rows[2][1] * column2[1] + m_Rows[2][2] * column2[2];
	matrix[2][2] = m_Rows[2][0] * column3[0] + m_Rows[2][1] * column3[1] + m_Rows[2][2] * column3[2];

	return matrix;
}

void Cinkes::CMat3x3::operator*=(const CMat3x3& a_Rhs)
{
	CMat3x3 matrix;
	CMat3x3 other = a_Rhs;
	CVector3 column1 = other.getColumn(0);
	CVector3 column2 = other.getColumn(1);
	CVector3 column3 = other.getColumn(2);
	matrix[0][0] = m_Rows[0][0] * column1[0] + m_Rows[0][1] * column1[1] + m_Rows[0][2] * column1[2];
	matrix[0][1] = m_Rows[0][0] * column2[0] + m_Rows[0][1] * column2[1] + m_Rows[0][2] * column2[2];
	matrix[0][2] = m_Rows[0][0] * column3[0] + m_Rows[0][1] * column3[1] + m_Rows[0][2] * column3[2];

	matrix[1][0] = m_Rows[1][0] * column1[0] + m_Rows[1][1] * column1[1] + m_Rows[1][2] * column1[2];
	matrix[1][1] = m_Rows[1][0] * column2[0] + m_Rows[1][1] * column2[1] + m_Rows[1][2] * column2[2];
	matrix[1][2] = m_Rows[1][0] * column3[0] + m_Rows[1][1] * column3[1] + m_Rows[1][2] * column3[2];

	matrix[2][0] = m_Rows[2][0] * column1[0] + m_Rows[2][1] * column1[1] + m_Rows[2][2] * column1[2];
	matrix[2][1] = m_Rows[2][0] * column2[0] + m_Rows[2][1] * column2[1] + m_Rows[2][2] * column2[2];
	matrix[2][2] = m_Rows[2][0] * column3[0] + m_Rows[2][1] * column3[1] + m_Rows[2][2] * column3[2];

	m_Rows[0] = matrix[0];
	m_Rows[1] = matrix[1];
	m_Rows[2] = matrix[2];

}

CMat3x3 Cinkes::CMat3x3::operator*(const CScalar& a_Rhs)
{
	return CMat3x3(m_Rows[0] * a_Rhs, m_Rows[1] * a_Rhs, m_Rows[2] * a_Rhs);
}


void CMat3x3::operator*=(const CScalar& a_Rhs)
{
	m_Rows[0] *= a_Rhs;
	m_Rows[1] *= a_Rhs;
	m_Rows[2] *= a_Rhs;
}

CVector3 CMat3x3::operator*(const CVector3& a_Rhs)
{
	CVector3 vector;

	vector[0] = m_Rows[0][0] * a_Rhs[0] + m_Rows[0][1] * a_Rhs[1] + m_Rows[0][2] * a_Rhs[2];
	vector[1] = m_Rows[1][0] * a_Rhs[0] + m_Rows[1][1] * a_Rhs[1] + m_Rows[1][2] * a_Rhs[2];
	vector[2] = m_Rows[2][0] * a_Rhs[0] + m_Rows[2][1] * a_Rhs[1] + m_Rows[2][2] * a_Rhs[2];

	return vector;
}

CVector3 CMat3x3::operator[](int a_Row) const
{
	return m_Rows[a_Row];
}

CVector3& CMat3x3::operator[](int a_Row)
{
	return m_Rows[a_Row];
}


CVector3 CMat3x3::getRow(int a_Row)
{
	return m_Rows[a_Row];
}

CVector3 CMat3x3::getColumn(int a_Column)
{
	return CVector3(m_Rows[0][a_Column], m_Rows[1][a_Column], m_Rows[2][a_Column]);

}

CMat3x3 CMat3x3::Transpose()
{
	CMat3x3 target;
	CVector3 column1 = CVector3(m_Rows[0][0], m_Rows[1][0], m_Rows[2][0]);
	CVector3 column2 = CVector3(m_Rows[0][1], m_Rows[1][1], m_Rows[2][1]);
	CVector3 column3 = CVector3(m_Rows[0][2], m_Rows[1][2], m_Rows[2][2]);
	target[0] = column1;
	target[1] = column2;
	target[2] = column3;

	return target;
}

CMat3x3 CMat3x3::GetInverse()
{
	CMat3x3 temp = (*this);
	CScalar determinant = temp.Determinant();
	if(determinant == 0 )
	{
		return GetIdentity();
	}

	temp = temp.Transpose();

	CMat3x3 calculatedMinors;
	calculatedMinors[0][0] = temp.DeterminantOfMinor(temp[1][1], temp[1][2], temp[2][1], temp[2][2]);
	calculatedMinors[0][1] = -temp.DeterminantOfMinor(temp[1][0], temp[1][2], temp[2][0], temp[2][2]);
	calculatedMinors[0][2] = temp.DeterminantOfMinor(temp[1][0], temp[1][1], temp[2][0], temp[2][1]);

	calculatedMinors[1][0] = -temp.DeterminantOfMinor(temp[0][1], temp[0][2], temp[2][1], temp[2][2]);
	calculatedMinors[1][1] = temp.DeterminantOfMinor(temp[0][0], temp[0][2], temp[2][0], temp[2][2]);
	calculatedMinors[1][2] = -temp.DeterminantOfMinor(temp[0][0], temp[0][1], temp[2][0], temp[2][1]);

	calculatedMinors[2][0] = temp.DeterminantOfMinor(temp[0][1], temp[0][2], temp[1][1], temp[1][2]);
	calculatedMinors[2][1] = -temp.DeterminantOfMinor(temp[0][0], temp[0][2], temp[1][0], temp[1][2]);
	calculatedMinors[2][2] = temp.DeterminantOfMinor(temp[0][0], temp[0][1], temp[1][0], temp[1][1]);

	CMat3x3 inverse = calculatedMinors * (1 / determinant);


	return inverse;
}

CMat3x3 CMat3x3::GetIdentity()
{
	return CMat3x3(1, 0, 0, 0, 1, 0, 0, 0, 1);
}

CScalar CMat3x3::Determinant()
{
	CScalar part1 = m_Rows[0][0] * (m_Rows[1][1] * m_Rows[2][2] - m_Rows[1][2] * m_Rows[2][1]);
	CScalar part2 = m_Rows[0][1] * (m_Rows[1][0] * m_Rows[2][2] - m_Rows[1][2] * m_Rows[2][0]);
	CScalar part3 = m_Rows[0][2] * (m_Rows[1][0] * m_Rows[2][1] - m_Rows[1][1] * m_Rows[2][0]);

	return part1 - part2 + part3;
}

CScalar Cinkes::CMat3x3::DeterminantOfMinor(CScalar a_00, CScalar a_01, CScalar a_10, CScalar a_11)
{
	CScalar a = a_00 * a_11;
	CScalar b = a_01 * a_10;

	return CScalar(a - b);
}

CQuaternion CMat3x3::ToQuaternion()
{
	CScalar trace = m_Rows[0][0] + m_Rows[1][1] + m_Rows[2][2];
	CQuaternion q;
		if (trace > 0) {
			CScalar S = CUtils::Sqrt(trace + CScalar(1.0)) * 2; // S=4*qw 
			q[3] = CScalar(0.25) * S;
			q[0] = (m_Rows[2][1] - m_Rows[1][2]) / S;
			q[1] = (m_Rows[0][2] - m_Rows[2][0]) / S;
			q[2] = (m_Rows[1][0] - m_Rows[0][1]) / S;
		}
		else if ((m_Rows[0][0] > m_Rows[1][1]) & (m_Rows[1][1] > m_Rows[2][2])) {
			CScalar S = CUtils::Sqrt(CScalar(1.0) + m_Rows[0][0] - m_Rows[1][1] - m_Rows[2][2]) * CScalar(2); // S=4*qx 
			q[3] = (m_Rows[2][1] - m_Rows[1][2]) / S;
			q[0] = CScalar(0.25) * S;
			q[1] = (m_Rows[0][1] + m_Rows[1][0]) / S;
			q[2] = (m_Rows[0][2] + m_Rows[2][0]) / S;
		}
		else if (m_Rows[1][1] > m_Rows[2][2]) {
			CScalar S = CUtils::Sqrt(CScalar(1.0) + m_Rows[1][1] - m_Rows[0][0] - m_Rows[2][2]) * CScalar(2); // S=4*qy
			q[3] = (m_Rows[0][2] - m_Rows[2][0]) / S;
			q[0] = (m_Rows[0][1] + m_Rows[1][0]) / S;
			q[1] = CScalar(0.25) * S;
			q[2] = (m_Rows[1][2] + m_Rows[2][1]) / S;
		}
		else {
			CScalar S = CUtils::Sqrt(CScalar(1.0) + m_Rows[2][2] - m_Rows[0][0] - m_Rows[1][1]) * CScalar(2); // S=4*qz
			q[3] = (m_Rows[1][0] - m_Rows[0][1]) / S;
			q[0] = (m_Rows[0][2] + m_Rows[2][0]) / S;
			q[1] = (m_Rows[1][2] + m_Rows[2][1]) / S;
			q[2] = static_cast<CScalar>(0.25) * S;
		}

		return q;
}

void CMat3x3::GetEuler(CScalar& a_Yaw, CScalar& a_Pitch, CScalar& a_Roll)
{
	if (m_Rows[0][0] == 1.0f)
	{
		a_Yaw = atan2f(m_Rows[0][2], m_Rows[1][2]);
		a_Pitch = 0;
		a_Roll = 0;

	}
	else if (m_Rows[0][0] == -1.0f)
	{
		a_Yaw = atan2f(m_Rows[0][2], m_Rows[1][2]);
		a_Pitch = 0;
		a_Roll = 0;
	}
	else
	{

		a_Yaw = atan2(-m_Rows[1][0], m_Rows[0][0]);
		a_Pitch = asin(m_Rows[2][2]);
		a_Roll = atan2(-m_Rows[2][1], m_Rows[2][2]);
	}


}


CMat3x3 CMat3x3::Abs()
{
	CMat3x3 matrix;
	matrix[0][0] = CUtils::Abs(m_Rows[0][0]);
	matrix[0][1] = CUtils::Abs(m_Rows[0][1]);
	matrix[0][2] = CUtils::Abs(m_Rows[0][2]);

	matrix[1][0] = CUtils::Abs(m_Rows[1][0]);
	matrix[1][1] = CUtils::Abs(m_Rows[1][1]);
	matrix[1][2] = CUtils::Abs(m_Rows[1][2]);

	matrix[2][0] = CUtils::Abs(m_Rows[2][0]);
	matrix[2][1] = CUtils::Abs(m_Rows[2][1]);
	matrix[2][2] = CUtils::Abs(m_Rows[2][2]);

	return matrix;
}
