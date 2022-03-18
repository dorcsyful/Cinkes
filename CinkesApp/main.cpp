
#include <iostream>
#include <OgreApplicationContext.h>

#include <OgreRoot.h>
#include <OgreEntity.h>
#include <OgreRenderWindow.h>
#include <windows.h>

#include "CinkesApp.h"

int main()
{
    using namespace Cinkes;
    bool go = true;
    Cinkes::CinkesApp app;
    app.initApp();

    Entity* mesh = app.m_SceneManager->createEntity("cube.mesh");
    SceneNode* ogreNode = app.m_SceneManager->getRootSceneNode()->createChildSceneNode();
    ogreNode->attachObject(mesh);
    mesh->setMaterialName("Ogre/Compositor/OldMovie");
    std::cout << std::endl << app.m_Go << std::endl;

    while(app.m_Go)
    {
        app.getRoot()->renderOneFrame();
        Sleep(100);

    }
    app.closeApp();
    return 0;
}
