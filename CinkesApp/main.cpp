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
    CCollisionWorld* world = new CCollisionWorld();
    std::shared_ptr<CBoxShape> shape = std::make_shared<CBoxShape>(CVector3(3, 3, 3));
    std::shared_ptr<CCollisionObject> object = std::make_shared<CCollisionObject>();
    object->SetCollisionShape(shape);
    object->SetTransform(CTransform(CVector3(0, 0, 0)));
    handler->RegisterObject(object);

    handler->m_Window->Run();

    delete world;
    delete handler;

    return 0;
}