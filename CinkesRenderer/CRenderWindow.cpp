#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "CCamera.h"
#include "CShader.h"
#include "CTexture.h"
#include "CRenderWindow.h"


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* a_Window, int a_Width, int a_Height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, a_Width, a_Height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* a_Window, double a_XposIn, double a_YposIn)
{
    Cinkes::CInputHandler* input = static_cast<Cinkes::CInputHandler*>(glfwGetWindowUserPointer(a_Window));
    float xpos = static_cast<float>(a_XposIn);
    float ypos = static_cast<float>(a_YposIn);

    if (input->m_FirstMouse)
    {
        input->m_LastX = xpos;
        input->m_LastY = ypos;
        input->m_FirstMouse = false;
    }

    float xoffset = xpos - input->m_LastX;
    float yoffset = input->m_LastY - ypos; // reversed since y-coordinates go from bottom to top

    input->m_LastX = xpos;
    input->m_LastY = ypos;
    input->AddMouseMovementToQueue(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* a_Window, double, double a_Yoffset)
{
    Cinkes::CInputHandler* input = static_cast<Cinkes::CInputHandler*>(glfwGetWindowUserPointer(a_Window));
    input->AddMouseScrollToQueue(static_cast<float>(a_Yoffset));
}

Cinkes::CRenderWindow::~CRenderWindow()
{

    glfwDestroyWindow(m_Window);
    glfwTerminate();

}

bool Cinkes::CRenderWindow::InitializeWindow()
{
    //glfw: setup
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(WIDTH, HEIGHT, "CinkesRenderer", NULL, NULL);
    if (m_Window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(m_Window);
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
    glfwSetCursorPosCallback(m_Window, mouse_callback);
    glfwSetScrollCallback(m_Window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    glEnable(GL_DEPTH_TEST);

    //Load shaders
    m_Shaders.insert(std::pair<std::string, std::shared_ptr<CShader>>("Base", std::make_shared<CShader>("../CinkesRenderer/resources/shaders/CShader.vs", "../CinkesRenderer/resources/shaders/CShader.fss")));
    m_Shaders.insert(std::pair<std::string, std::shared_ptr<CShader>>("Line", std::make_shared<CShader>("../CinkesRenderer/resources/shaders/CLineShader.vs", "../CinkesRenderer/resources/shaders/CLineShader.fss")));
    m_Shaders.insert(std::pair<std::string, std::shared_ptr<CShader>>("Light", std::make_shared<CShader>("../CinkesRenderer/resources/shaders/CLightSourceShader.vs", "../CinkesRenderer/resources/shaders/CLightSourceShader.fss")));
    m_Shaders.insert(std::pair<std::string, std::shared_ptr<CShader>>("SkyBox", std::make_shared<CShader>("../CinkesRenderer/resources/shaders/CSkyBoxShader.vs", "../CinkesRenderer/resources/shaders/CSkyBoxShader.fss")));
    m_LightHandler = std::make_shared<CLightHandler>();


	//Create two point lights
    auto temp = std::make_shared<CPointLightShape>(glm::vec3(5, 5, 15));
	m_LightHandler->AddPointLight(temp);
	auto temp2 = std::make_shared<CPointLightShape>(glm::vec3(5, 10, 15));
    m_LightHandler->AddPointLight(temp2);
    glfwSetWindowUserPointer(m_Window, m_Input.get());
    m_SkyBox = std::make_shared<CSkyBox>();
	return true;
}

void Cinkes::CRenderWindow::Update()
{
}

bool Cinkes::CRenderWindow::AddRenderShape(std::shared_ptr<CRenderShape>& a_Shape)
{
    m_Shapes.push_back(a_Shape);
    return true;

}

bool Cinkes::CRenderWindow::AddLine(std::shared_ptr<CLineRendered>& a_Lines)
{
    m_Lines.push_back(a_Lines);
    return true;
}

bool Cinkes::CRenderWindow::AddLine(const glm::vec3& a_Start, const glm::vec3& a_End, const glm::vec3& a_Color)
{
    std::shared_ptr<CLineRendered> lines = std::make_shared<CLineRendered>(a_Start, a_End, a_Color);
    m_Lines.push_back(lines);
    return true;
}

bool Cinkes::CRenderWindow::RemoveRenderShapeByObject(std::shared_ptr<CRenderShape>& a_Shape)
{

    return false;
}

bool Cinkes::CRenderWindow::RemoveRenderShapeByIndex(unsigned int a_Index)
{

    return false;
}
bool Cinkes::CRenderWindow::RenderUpdate()
{

    
    if (glfwWindowShouldClose(m_Window)) { return true; }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_Input->m_Camera->m_Wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }

    glm::mat4 projection = glm::perspective(glm::radians(m_Input->m_Camera->m_FOV), static_cast<float>(WIDTH / HEIGHT), 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(m_Input->m_Camera->m_Position, m_Input->m_Camera->m_Position + m_Input->m_Camera->m_Front, m_Input->m_Camera->m_Up);

    //Draw light shapes
    m_Shaders["Light"]->Use();
    m_Shaders["Light"]->setMat4("projection", projection);
    m_Shaders["Light"]->setMat4("view", view);
    for(int i = 0; i < std::max(m_LightHandler->m_PointLights.size(), m_LightHandler->m_DirectionalLights.size()); i++)
    {
        if(i < m_LightHandler->m_PointLights.size())
        {
            if (m_LightHandler->m_PointLights[i]->m_DrawLightSource) {
                glBindVertexArray(m_LightHandler->m_PointLights[i]->m_Shape->GetVAO());

                m_Shaders["Light"]->setVec3("color", m_LightHandler->m_PointLights[i]->m_Shape->GetMaterial()->m_Color);
                m_Shaders["Light"]->setMat4("model", m_LightHandler->m_PointLights[i]->m_Shape->GetTransform());

                glDrawArrays(GL_TRIANGLES, 0, m_LightHandler->m_PointLights[i]->m_Shape->m_Vertices.size());
            }
        }
        if (i < m_LightHandler->m_DirectionalLights.size())
        {
            if (m_LightHandler->m_DirectionalLights[i]->m_DrawLightSource) {
                glBindVertexArray(m_LightHandler->m_DirectionalLights[i]->m_Shape->GetVAO());

                m_Shaders["Light"]->setVec3("color", m_LightHandler->m_DirectionalLights[i]->m_Shape->GetMaterial()->m_Color);
                m_Shaders["Light"]->setMat4("model", m_LightHandler->m_DirectionalLights[i]->m_Shape->GetTransform());

                glDrawArrays(GL_TRIANGLES, 0, m_LightHandler->m_DirectionalLights[i]->m_Shape->m_Vertices.size());
            }
        }
    }

    //Draw actual shapes with lighting
    m_Shaders["Base"]->Use();
    m_Shaders["Base"]->setMat4("projection", projection);
    m_Shaders["Base"]->setMat4("view", view);
    m_Shaders["Base"]->setVec3("viewPos", m_Input->m_Camera->m_Position);
    m_LightHandler->AssignPointLightData(m_Shaders["Base"]);
    m_LightHandler->AssignDirectionalLightData(m_Shaders["Base"]);

	for (const auto& shape : m_Shapes)
    {
        m_Shaders["Base"]->setInt("hasTexture", shape->GetMaterial()->m_BaseColorTexture.isValid);

        //I am Dori and this is where I bind my material
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, shape->GetMaterial()->m_BaseColorTexture.m_Texture);
        m_Shaders["Base"]->setVec3("baseColor", shape->GetMaterial()->m_Color);


        //I am also Dori and this is where I bind my geometry
    	glBindVertexArray(shape->GetVAO());
        m_Shaders["Base"]->setMat4("model", shape->GetTransform());
        
        glDrawArrays(GL_TRIANGLES, 0, shape->m_Vertices.size());
    }

    //Special code for lines
    m_Shaders["Line"]->Use();
	glLineWidth(1);

    for (auto& line : m_Lines) {
        m_Shaders["Line"]->setMat4("MVP", projection * view);
        m_Shaders["Line"]->setVec3("color", line->m_Color);

        glBindVertexArray(line->m_VAO);
        glDrawArrays(GL_LINE_LOOP, 0, 2);
        glBindVertexArray(0);
    }


    // draw skybox as last
    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    m_Shaders["SkyBox"]->Use();
    view = glm::mat4(glm::mat3(m_Input->m_Camera->GetViewMatrix())); // remove translation from the view matrix
    m_Shaders["SkyBox"]->setMat4("view", view);
    m_Shaders["SkyBox"]->setMat4("projection", projection);
    // skybox cube
    glBindVertexArray(m_SkyBox->m_VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_SkyBox->m_TextureID);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default


	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
    m_Input->ProcessInput(m_Window);




    return false;
}

void Cinkes::CRenderWindow::CreateMaterial(const glm::vec3& a_BaseColor, const std::string& a_BaseTexturePath)
{
}
