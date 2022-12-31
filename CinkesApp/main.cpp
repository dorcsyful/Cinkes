#pragma once
#include "CRenderWindow.h"
#include "CRenderDefines.h"
int main()
{
    using namespace Cinkes;


    CRenderWindow* window = new CRenderWindow();
    std::shared_ptr<CRenderShape> shape1 = std::make_shared<CRenderShape>();
    window->AddRenderShape(shape1);
    window->InitializeWindow();
    shape1->CreateVBO();
    shape1->LoadTexture(TEXTURE, window->m_Shader.get());





    window->Run();

    delete window;

    return 0;
}