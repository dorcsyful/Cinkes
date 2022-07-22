#include <iostream>

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
    rigidBody->GetTransform().setOrigin(CVector3(0, 60, 0));
    app->AddObject(rigidBody, "cube.mesh", "Examples/Robot");

    std::shared_ptr<CCollisionObject >collision_object = std::make_shared<CCollisionObject>();
    collision_object->SetCollisionShape(shape);
    collision_object->GetTransform().setOrigin(CVector3(0, -60, 0));
    app->AddObject(collision_object, "cube.mesh", "Ogre/Skin");
	physics_world->GetGeneratorRegistry()->GetGeneratorByType(EGENERATOR_TYPE::TYPE_GRAVITY)->RemoveObjectByValue(collision_object.get());

    while (app->m_Go)
    {

        physics_world->Update(0.6);
        app->Convert();
        std::cout << "Position in renderer: " << app->m_Converters[0]->m_Cinkes->GetTransform().getOrigin().getY() << std::endl;
        Sleep(1000);

        app->getRoot()->renderOneFrame();

    }
    app->closeApp();
    return 0;
}
