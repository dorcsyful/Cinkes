#include "CCollisionResolver.h"

#include "CCollisionObject.h"
#include "CUtils.h"
#include "CVector3.h"
#include "CInternalContactInfo.h"
#include "CQuaternion.h"
#include "CRigidBody.h"

bool Cinkes::CCollisionResolver::Resolve(std::vector<std::shared_ptr<CInternalContactInfo>>& a_Info, CScalar a_T) const
{
	return true;
}
