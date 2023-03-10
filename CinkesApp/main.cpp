#include "CRenderWindow.h"
#include "CRenderHandler.h"
#include "CCollisionWorld.h"
#include "CBoxShape.h"
#include "CPhysicsWorld.h"

int main()
{
    using namespace Cinkes;
    
    CRenderHandler* handler = new CRenderHandler(true);

	/*CTransform transform = CTransform(CMat3x3(0.7071068f, -0.7071068f, 0.f,
		0.7071068f, 0.7071068f, 0.f,
		0.f, 0.f, 1.f), CVector3(5, 13, 0));*/
	//std::shared_ptr<CBoxShape> shape1 = std::make_shared<CBoxShape>(2, 3, 3);
	std::shared_ptr<CBoxShape> shape2 = std::make_shared<CBoxShape>(3, 1, 2);
	//std::shared_ptr<CCollisionObject> object1 = std::make_shared<CCollisionObject>(CVector3(5, 7, 0), shape2);
	//std::shared_ptr<CCollisionObject> object2 = std::make_shared<CCollisionObject>(transform, shape1);
    std::unique_ptr<CPhysicsWorld> world = std::make_unique<CPhysicsWorld>();

    std::shared_ptr<CRigidBody> rb1 = std::make_shared<CRigidBody>(CTransform(CVector3(0, 0, 10)),shape2);
    world->AddRigidBody(rb1);
    CSpringData data;
    data.m_Body[0] = rb1.get();
    data.m_Points[1] = CVector3(0, 10, 10);
    data.m_RestLength = 5;
    data.m_SpringConstant = 2.5f;
    data.m_DampeningConstant = 0.4f;
    std::shared_ptr<CSpring> spring = std::make_shared<CSpring>(data);
    //world->RunCollision(1);
    world->AddSpring(spring);
    handler->RegisterObject(rb1);
    double last = 0;
    float interval = 1.f / 120.f;
    while(true)
    {
        double now = glfwGetTime();
        auto elapsed = now - last;
        if(elapsed > interval)
        {
            last = now;
    		world->Update(elapsed);
            std::cout << rb1->GetTransform().getOrigin().getY() << std::endl;
	        
        }
        if (handler->m_Window->RenderUpdate()) { break; }

        handler->UpdateObjects();
    }
    
    delete handler;

    return 0;
}
