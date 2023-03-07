#include "CRenderWindow.h"
#include "CRenderHandler.h"
#include "CCollisionWorld.h"
#include "CBoxShape.h"
int main()
{
    using namespace Cinkes;
    
    CRenderHandler* handler = new CRenderHandler(true);

	CTransform transform = CTransform(CMat3x3(0.7071068f, -0.7071068f, 0.f,
		0.7071068f, 0.7071068f, 0.f,
		0.f, 0.f, 1.f), CVector3(5, 13, 0));
	std::shared_ptr<CBoxShape> shape1 = std::make_shared<CBoxShape>(2, 3, 3);
	std::shared_ptr<CBoxShape> shape2 = std::make_shared<CBoxShape>(3, 4, 3);
	std::shared_ptr<CCollisionObject> object1 = std::make_shared<CCollisionObject>(CVector3(5, 7, 0), shape2);
	std::shared_ptr<CCollisionObject> object2 = std::make_shared<CCollisionObject>(transform, shape1);

    handler->RegisterObject(object1);
    handler->RegisterObject(object2);

    std::unique_ptr<CCollisionWorld> world = std::make_unique<CCollisionWorld>();
    world->AddObject(object1);
    world->AddObject(object2);
    world->RunCollision(1);


    while(true)
    {
        if (handler->m_Window->RenderUpdate()) { break; }
    }
    
    delete handler;

    return 0;
}