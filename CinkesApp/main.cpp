#include "CVector3.h"
#include "CBoxShape.h"
#include "CinkesApp.h"
#include "CPhysicsWorld.h"
#include <Windows.h>

int main()
{
    using namespace Cinkes;
    std::unique_ptr<CinkesApp> app = std::make_unique<CinkesApp>();
    app->initApp();

    std::unique_ptr<CPhysicsWorld> physics_world = std::make_unique<CPhysicsWorld>();
    app->m_PhysicsWorld = physics_world.get();

    std::shared_ptr<CBoxShape> shape = std::make_shared<CBoxShape>();
    shape->SetDimensions(CVector3(50, 50, 50));
    std::shared_ptr<CRigidBody> rigidBody = std::make_shared<CRigidBody>();
    rigidBody->SetCollisionShape(shape);
    //app->AddObject(rigidBody);

    rigidBody = std::make_shared<CRigidBody>();
    rigidBody->SetCollisionShape(shape);
    rigidBody->GetTransform().setOrigin(CVector3(0, -50, 0));
    app->AddObject(rigidBody);

    physics_world->GetGeneratorRegistry()->GetGeneratorByType(EGENERATOR_TYPE::TYPE_GRAVITY)->RemoveObjectByValue(rigidBody.get());

    while (app->m_Go)
    {
        app->getRoot()->renderOneFrame();

        physics_world->Update(0.6);
        app->Convert();
        Sleep(1000);

    }
    app->closeApp();
    return 0;
}
