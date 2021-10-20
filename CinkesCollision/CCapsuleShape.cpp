#include "CCapsuleShape.h"
#include "CCapsuleShape.h"
#include "../CinkesMath/CUtils.h"


Cinkes::CVector3 Cinkes::CCapsuleShape::Support(const CVector3& a_V)
{
    CVector3 segment = CVector3(m_Height * a_V[0], 0, 0);
    return segment + (a_V * m_Radius);
}
