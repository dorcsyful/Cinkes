#pragma once
#include "CRenderWindow.h"
#include "CRenderDefines.h"
#include "CRenderHandler.h"
#include "CCollisionWorld.h"
#include "CBoxShape.h"
int main()
{
    using namespace Cinkes;
    
    CRenderHandler* handler = new CRenderHandler(true);
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


    handler->RegisterObject(object1);
    handler->RegisterObject(object2);

    handler->m_Window->Run();

    delete handler;

    return 0;
}