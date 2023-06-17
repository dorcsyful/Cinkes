#include "CRenderWindow.h"
#include "CRenderHandler.h"
#include "CCollisionWorld.h"
#include "CBoxShape.h"
#include "CPhysicsWorld.h"

int main()
{
    using namespace Cinkes;
    
    CRenderHandler* handler = new CRenderHandler(true);
        CTransform transform = CTransform(CMat3x3(/*0.7071068f, -0.7071068f, 0.f,
            0.7071068f, 0.7071068f, 0.f,
            0.f, 0.f, 1.f*/), CVector3(0, 5, 10));
            std::shared_ptr<CBoxShape> shape1 = std::make_shared<CBoxShape>(2, 3, 3);
        std::shared_ptr<CCollisionObject> object1 = std::make_shared<CCollisionObject>(CVector3(0, 5, 10), shape1);
        std::shared_ptr<CRigidBody> object2 = std::make_shared<CRigidBody>(transform, shape1, 1);
        std::unique_ptr<CPhysicsWorld> world = std::make_unique<CPhysicsWorld>();
        CMat3x3 rolled = CMat3x3(0, 1, 0,
            0, 0, -1,
            -1, 0, 0);
        world->AddRigidBody(object2);

        CSpringData data;
        data.m_Body[0] = object2.get();
        data.m_Points[1] = CVector3(0, 5, 10);
        data.m_Points[0] = CVector3(0, 0,0);
        data.m_RestLength = 4;
        data.m_SpringConstant = 10.f;
        data.m_DampeningConstant = 2.f;
        std::shared_ptr<CSpring> spring = std::make_shared<CSpring>(data);
        //world->RunCollision(1);
        world->AddSpring(spring);


    std::shared_ptr<CMaterial> material = std::make_shared<CMaterial>();
    material->m_BaseColorTexture.CreateTexture("../CinkesRenderer/resources/images/testure.jpg");

    handler->RegisterObject(object2);
    handler->GetWrapperByIndex(0).m_RenderObject->SetMaterial(material);
    double last = 0;
    float interval = 1.f / 120.f;
    while(true)
    {
        double now = glfwGetTime();
        auto elapsed = now - last;
        if(elapsed > interval)
        {
            world->Update(elapsed);
            last = now;

        if (handler->m_Window->RenderUpdate()) { break; }

        handler->UpdateObjects();	        
        }

    }
    
    delete handler;

    return 0;
}
