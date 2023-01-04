#include "CRenderShape.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
Cinkes::CRenderShape::CRenderShape()
{

    m_Transform = glm::mat4(1.f);
    m_Transform = glm::mat4(1.f);
    m_Transform = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    m_Transform = glm::translate(m_Transform, glm::vec3(0, -20, -10));
    std::cout << m_Transform[0][0] << " " << m_Transform[0][1] << " " << m_Transform[0][2] << std::endl;
    std::cout << m_Transform[1][0] << " " << m_Transform[1][1] << " " << m_Transform[1][2] << std::endl;
    std::cout << m_Transform[2][0] << " " << m_Transform[2][1] << " " << m_Transform[2][2] << std::endl;

}

int Cinkes::CRenderShape::CreateVBO()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CVertex) * m_Vertices.size(), m_Vertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CVertex), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(CVertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    return m_VBO;
}

bool Cinkes::CRenderShape::LoadTexture(std::string a_Path, CShader* a_Shader)
{
    m_Texture = std::make_shared<CTexture>();
    return m_Texture->CreateTexture(a_Shader, a_Path);
}

glm::mat4 Cinkes::CRenderShape::Convert()
{
    return glm::mat4();
}

