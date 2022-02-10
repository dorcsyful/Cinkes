#include "CTransform.h"

#include <algorithm>
#include <cassert>

#include "CQuaternion.h"
using namespace Cinkes;

Cinkes::CTransform::CTransform()
{
	setIdentity();
}

Cinkes::CTransform::CTransform(const CMat3x3& a_Basis, const CVector3& a_Origin)
{
	m_Basis = a_Basis;
	m_Origin = a_Origin;
}

Cinkes::CTransform::CTransform(const CTransform& a_Rhs)
{
	m_Basis = a_Rhs.getBasis();
	m_Origin = a_Rhs.getOrigin();
}

Cinkes::CTransform::CTransform(CTransform&& a_Rhs) noexcept
{
	m_Basis = a_Rhs.getBasis();
	m_Origin = a_Rhs.getOrigin();
}

void Cinkes::CTransform::operator*=(const CTransform& a_Rhs)
{
	m_Origin += m_Basis * a_Rhs.m_Origin;
	m_Basis *= a_Rhs.m_Basis;
}

CTransform Cinkes::CTransform::operator*(const CTransform& a_Rhs)
{
	return CTransform(m_Basis * a_Rhs.m_Basis,
		(*this)(a_Rhs.m_Origin));
}

CVector3 Cinkes::CTransform::operator*(const CVector3& a_Rhs)
{
	return {
		a_Rhs[0] * getBasis()[0][0] +
		a_Rhs[1] * getBasis().getColumn(0)[1] +
		a_Rhs[2] * getBasis().getColumn(0)[2] + getOrigin().getX(),

		a_Rhs[0] * getBasis().getRow(0)[1] +
		a_Rhs[1] * getBasis().getColumn(1)[1] +
		a_Rhs[2] * getBasis().getColumn(1)[2] + getOrigin().getY(),

		a_Rhs[0] * getBasis().getRow(0)[2] +
		a_Rhs[1] * getBasis().getRow(1)[2] +
		a_Rhs[2] * getBasis().getColumn(2)[1] + getOrigin().getZ()
	};
}

CTransform& Cinkes::CTransform::operator=(CTransform&& a_Rhs) noexcept
{
	m_Basis = a_Rhs.getBasis();
	m_Origin = a_Rhs.getOrigin();

	return (*this);
}

CTransform& Cinkes::CTransform::operator=(const CTransform& a_Rhs)
{
	m_Basis = a_Rhs.getBasis();
	m_Origin = a_Rhs.getOrigin();

	return (*this);
}

bool Cinkes::CTransform::operator==(const CTransform& a_Rhs)
{
	return (m_Basis == a_Rhs.getBasis()) && (m_Origin == a_Rhs.getOrigin());
}

bool Cinkes::CTransform::operator!=(const CTransform& a_Rhs)
{
	return (m_Basis != a_Rhs.getBasis()) || (m_Origin != a_Rhs.getOrigin());

}

CVector3 Cinkes::CTransform::operator()(const CVector3& a_Rhs)
{
	CVector3 temp = a_Rhs;
	return temp.Dot3(m_Basis[0], m_Basis[1], m_Basis[2]) + m_Origin;
}

void Cinkes::CTransform::Multiply(const CTransform& a_Lhs, const CTransform& a_Rhs)
{
	CTransform lhs = a_Lhs;
	CTransform rhs = a_Rhs;
	m_Basis = lhs.m_Basis * rhs.m_Basis;
	m_Origin = lhs(a_Rhs.m_Origin);
}

CMat3x3 Cinkes::CTransform::getBasis()
{
	return m_Basis;
}

CMat3x3 Cinkes::CTransform::getBasis() const
{
	return m_Basis;
}

CVector3 CTransform::getOrigin()
{
	return m_Origin;
}

CVector3 Cinkes::CTransform::getOrigin() const
{
	return m_Origin;
}

CScalar Cinkes::CTransform::getPerValue(unsigned a_Value)
{
	assert(a_Value < 12);
	if (a_Value <= 2) { return m_Basis.getColumn(0)[a_Value]; }
	if (a_Value == 3) { return m_Origin.getX(); }
	if (4 <= a_Value && a_Value <= 6) { return m_Basis.getColumn(1)[a_Value - 4]; }
	if (a_Value == 7) { return m_Origin.getY(); }
	if (8 <= a_Value && a_Value <= 10) { return m_Basis.getColumn(2)[a_Value - 8]; }
	if (a_Value == 11) { return m_Origin.getZ(); }
	assert(false); 
	return std::numeric_limits<CScalar>::max();
}

CScalar Cinkes::CTransform::getPerValue(unsigned a_Value) const
{
	assert(a_Value < 12);
	if (a_Value <= 2) { return m_Basis.getColumn(0)[a_Value]; }
	if (a_Value == 3) { return m_Origin.getX(); }
	if (4 <= a_Value && a_Value <= 6) { m_Basis.getColumn(1)[a_Value - 4]; }
	if (a_Value == 7) { return m_Origin.getY(); }
	if (8 <= a_Value && a_Value <= 10) { return m_Basis.getColumn(2)[a_Value - 8]; }
	if (a_Value == 11) { return m_Origin.getZ(); }
	assert(0 == 0);
	return std::numeric_limits<CScalar>::max();
}

CVector3 Cinkes::CTransform::getAxisVector(unsigned a_Value)
{
	return CVector3(getPerValue(a_Value), getPerValue(a_Value + 4), getPerValue(a_Value + 8));

}

CVector3 Cinkes::CTransform::getAxisVector(unsigned a_Value) const
{
	return CVector3(getPerValue(a_Value), getPerValue(a_Value + 4), getPerValue(a_Value + 8));

}


CQuaternion Cinkes::CTransform::getQuaternion()
{
	return m_Basis.ToQuaternion();
}

void Cinkes::CTransform::setBasis(const CMat3x3& a_Rhs)
{
	m_Basis = a_Rhs;
}

void Cinkes::CTransform::setOrigin(const CVector3& a_Rhs)
{
	m_Origin = a_Rhs;
}

void Cinkes::CTransform::setIdentity()
{
	m_Basis = CMat3x3();
	m_Origin = CVector3();
}

CTransform Cinkes::CTransform::getIdentity()
{
	return CTransform(CMat3x3(),CVector3());
}

CTransform Cinkes::CTransform::Inverse()
{
	CMat3x3 inv = m_Basis.Transpose();
	CVector3 origin = m_Origin * (-1);
	origin = inv * origin;
	return CTransform(inv,origin);

}
