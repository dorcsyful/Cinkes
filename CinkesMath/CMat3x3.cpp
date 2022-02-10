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

Cinkes::CMat3x3::CMat3x3(const CVector3& a_Axis, CScalar a_Angle)
{
	SetFromAxisAngle(a_Axis, a_Angle);
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

Cinkes::CMat3x3::CMat3x3(const CQuaternion& a_Rotation)
{
	CScalar sqw = a_Rotation[3] * a_Rotation[3];
	CScalar sqx = a_Rotation[0] * a_Rotation[0];
	CScalar sqy = a_Rotation[1] * a_Rotation[1];
	CScalar sqz = a_Rotation[2] * a_Rotation[2];

	// invs (inverse square length) is only required if quaternion is not already normalised
	CScalar invs = 1 / (sqx + sqy + sqz + sqw);
	m_Rows[0][0] = (sqx - sqy - sqz + sqw) * invs; // since sqw + sqx + sqy + sqz =1/invs*invs
	m_Rows[1][1] = (-sqx + sqy - sqz + sqw) * invs;
	m_Rows[2][2] = (-sqx - sqy + sqz + sqw) * invs;

	CScalar tmp1 = a_Rotation[0] * a_Rotation[1];
	CScalar tmp2 = a_Rotation[2] * a_Rotation[3];
	m_Rows[1][0] = static_cast<float>(2.0) * (tmp1 + tmp2) * invs;
	m_Rows[0][1] = static_cast<float>(2.0) * (tmp1 - tmp2) * invs;

	tmp1 = a_Rotation[0] * a_Rotation[2];
	tmp2 = a_Rotation[1] * a_Rotation[3];
	m_Rows[2][0] = static_cast<CScalar>(2.0) * (tmp1 - tmp2) * invs;
	m_Rows[0][2] = static_cast<CScalar>(2.0) * (tmp1 + tmp2) * invs;
	tmp1 = a_Rotation[1] * a_Rotation[2];
	tmp2 = a_Rotation[0] * a_Rotation[3];
	m_Rows[2][1] = static_cast<CScalar>(2.0) * (tmp1 + tmp2) * invs;
	m_Rows[1][2] = static_cast<CScalar>(2.0) * (tmp1 - tmp2) * invs;
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

CVector3 CMat3x3::operator[](unsigned a_Row) const
{
	return m_Rows[a_Row];
}

CVector3& CMat3x3::operator[](unsigned a_Row)
{
	return m_Rows[a_Row];
}

CVector3 Cinkes::CMat3x3::getRow(unsigned a_Row) const
{
	return m_Rows[a_Row];
}


CVector3 CMat3x3::getRow(unsigned a_Row)
{
	return m_Rows[a_Row];
}

CVector3 CMat3x3::getColumn(unsigned a_Column)
{
	return {m_Rows[0][a_Column], m_Rows[1][a_Column], m_Rows[2][a_Column]};

}

CVector3 Cinkes::CMat3x3::getColumn(unsigned a_Column) const
{
	return {m_Rows[0][a_Column], m_Rows[1][a_Column], m_Rows[2][a_Column]};

}

void CMat3x3::setColumn(unsigned a_Num, const CVector3& a_Column)
{
	m_Rows[0][a_Num] = a_Column.getX();
	m_Rows[1][a_Num] = a_Column.getY();
	m_Rows[2][a_Num] = a_Column.getZ();
}

void Cinkes::CMat3x3::setFromColumns(const CVector3& a_0, const CVector3& a_1, const CVector3& a_2)
{
	setColumn(0, a_0);
	setColumn(1, a_1);
	setColumn(2, a_2);
}

void Cinkes::CMat3x3::setSkewSymmetric(const CVector3& a_Vector)
{
	m_Rows[0][0] = m_Rows[1][1] = m_Rows[2][2] = 0;
	m_Rows[1][0] = -a_Vector.getZ();
	m_Rows[2][0] = a_Vector.getY();
	m_Rows[0][1] = a_Vector.getZ();
	m_Rows[2][1] = -a_Vector.getX();
	m_Rows[0][2] = -a_Vector.getY();
	m_Rows[1][2] = a_Vector.getZ();
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

CVector3 Cinkes::CMat3x3::TransformTranspose(const CVector3& a_Vector)
{
	return CVector3(
		a_Vector.getX() * m_Rows[0][0] + a_Vector.getY() * m_Rows[0][1] + a_Vector.getZ() * m_Rows[2][2],
		a_Vector.getX() * m_Rows[1][0] + a_Vector.getY() * m_Rows[1][1] + a_Vector.getZ() * m_Rows[2][2],
		a_Vector.getX() * m_Rows[2][0] + a_Vector.getY() * m_Rows[2][1] + a_Vector.getZ() * m_Rows[2][2]);
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

void Cinkes::CMat3x3::SetFromAxisAngle(const CVector3& a_Axis, CScalar a_Angle)
{
	CScalar cos = CUtils::Cos(a_Angle);
	CScalar sin = CUtils::Sin(a_Angle);
	CScalar t = 1 - cos;

	CScalar xyt = a_Axis.getX() * a_Axis.getY() * t;
	CScalar zsin = a_Axis.getZ() * sin;
	CScalar xzt = a_Axis.getX() * a_Axis.getZ() * t;
	CScalar ysin = a_Axis.getY() * sin;
	CScalar xsin = a_Axis.getX() * sin;
	CScalar yzt = a_Axis.getY() * a_Axis.getZ() * t;

	m_Rows[0][0] = cos + a_Axis.getX() * a_Axis.getX() * t;
	m_Rows[0][1] = xyt - zsin;
	m_Rows[0][2] = xzt + ysin;
	m_Rows[1][0] = xyt + zsin;
	m_Rows[1][1] = cos + a_Axis.getY() * a_Axis.getY() * t;
	m_Rows[1][2] = yzt - xsin;
	m_Rows[2][0] = xzt - ysin;
	m_Rows[2][1] = xyt + xsin;
	m_Rows[2][2] = t * a_Axis.getZ() * a_Axis.getZ() + cos;
	
}
