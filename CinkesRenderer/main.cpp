#pragma once
#include "CRenderWindow.h"
#include "CRenderShape.h"
int main()
{
    using namespace Cinkes;
    std::vector<glm::vec3> cubePositions = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    CRenderWindow* window = new CRenderWindow();
    std::shared_ptr<CRenderShape> shape1 = std::make_shared<CRenderShape>();
    window->AddRenderShape(shape1);
    window->InitializeWindow(800, 600, 4, 6);
    shape1->CreateVBO();
    shape1->LoadTexture("resources/images/testure.jpg", window->m_Shader.get());





    window->Run();

    delete window;

    return 0;
}