#include "CRenderShape.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <utility>
int Cinkes::CRenderShape::CreateVBO()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_IBO);
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

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(CVertex), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);



    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return m_VBO;
}

bool Cinkes::CRenderShape::LoadTexture(const std::string& a_Path, CShader* a_Shader)
{
    m_Texture = std::make_shared<CTexture>();
    return m_Texture->CreateTexture(a_Shader, a_Path);
}

glm::mat4 Cinkes::CRenderShape::Convert()
{
    return glm::mat4();
}

Cinkes::CLineRendered::CLineRendered(const glm::vec3& a_Start, const glm::vec3& a_End, const glm::vec3& a_Color, float a_Width)
{
    m_Vertices[0] = a_Start;
    m_Vertices[1] = a_End;
    m_Color = a_Color;
    m_Width = a_Width;
    m_Full = std::vector<float>(6);
    m_Full[0] = a_Start[0]; m_Full[1] = a_Start[1]; m_Full[2] = a_Start[2];
    m_Full[3] = a_End[0]; m_Full[4] = a_End[1]; m_Full[5] = a_End[2];

    CreateVBO();
}

int Cinkes::CLineRendered::CreateVBO()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Full.size(), m_Full.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return 0;
}
