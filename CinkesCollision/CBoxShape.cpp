#include "CBoxShape.h"
#include "CBoxShape.h"
#include "../CinkesMath/CUtils.h"
Cinkes::CVector3 Cinkes::CBoxShape::Support(const CVector3& a_V)
{
	return CVector3(m_Dimensions[0] * CUtils::Sgn(1,a_V[0]),
						m_Dimensions[1] * CUtils::Sgn(1, a_V[1]),
						m_Dimensions[2] * CUtils::Sgn(1, a_V[2]));
}
