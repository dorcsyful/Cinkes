
#include "CCollisionWorld.h"
#include "CBoxShape.h"
#include "CEPA.h"
int main()
{
    using namespace Cinkes;
    

    CGJKAlgorithm gjk;
	CEPA epa;
	CTransform transform = CTransform(CMat3x3(0.7071068f, -0.7071068f, 0.f,
		0.7071068f, 0.7071068f, 0.f,
		0.f, 0.f, 1.f), CVector3(5, 13, 2));
	std::shared_ptr<CBoxShape> shape1 = std::make_shared<CBoxShape>(2, 3, 3);
	std::shared_ptr<CBoxShape> shape2 = std::make_shared<CBoxShape>(3, 4, 3);
	std::shared_ptr<CCollisionObject> object1 = std::make_shared<CCollisionObject>(CVector3(3, 7, 0), shape2);
	std::shared_ptr<CCollisionObject> object2 = std::make_shared<CCollisionObject>(transform, shape1);
	CSimplex simplex;
	std::shared_ptr<CInternalContactInfo> info = std::make_shared<CInternalContactInfo>();
	bool algo = gjk.Algorithm(object1.get(), object2.get(), simplex);
	if (algo) {
		info->m_First = object1;
		object1->SetHasContact(info.get());
		object2->SetHasContact(info.get());
		info->m_Second = object2;

		epa.Algorithm(info.get(), simplex);
	}

	


    return 0;
}