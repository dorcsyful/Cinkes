#include "CTransform.h"
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
