#include "CVector3.h"
#include "CBoxShape.h"
#include "CinkesApp.h"
#include "CPhysicsWorld.h"
#include <windows.h>
int main()
{
    using namespace Cinkes;
	std::unique_ptr<CinkesApp> app = std::make_unique<CinkesApp>();
    app->initApp();

    std::unique_ptr<CPhysicsWorld> physicsWorld = std::make_unique<CPhysicsWorld>();
    app->m_PhysicsWorld = physicsWorld.get();
    std::shared_ptr<CBoxShape> shape = std::make_shared<CBoxShape>();
    shape->SetDimensions(CVector3(10, 10, 10));
    std::shared_ptr<CRigidBody> rigidBody = std::make_shared<CRigidBody>();
    rigidBody->SetCollisionShape(shape);

    app->AddObject(rigidBody);

    while(app->m_Go)
    {
        //rigidBody->AddForce(CVector3(10, 0, 0));
        physicsWorld->Update(1);
        app->Convert();
        Sleep(100);
        app->getRoot()->renderOneFrame();

    }
    app->closeApp();
    return 0;
}
