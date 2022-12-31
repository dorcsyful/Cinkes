#include "CRenderWindow.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CCamera.h"
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    CInputHandler* input =  static_cast<CInputHandler*>(glfwGetWindowUserPointer(window));
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (input->firstMouse)
    {
        input->lastX = xpos;
        input->lastY = ypos;
        input->firstMouse = false;
    }

    float xoffset = xpos - input->lastX;
    float yoffset = input->lastY - ypos; // reversed since y-coordinates go from bottom to top

    input->lastX = xpos;
    input->lastY = ypos;
    input->AddMouseMovementToQueue(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    CInputHandler* input = static_cast<CInputHandler*>(glfwGetWindowUserPointer(window));
    input->AddMouseScrollToQueue(yoffset);
}

CRenderWindow::CRenderWindow(int a_Width, int a_Height, int a_Version_Major, int a_Version_Minor)
{
    InitializeWindow(800, 600, a_Version_Major, a_Version_Minor);
}

CRenderWindow::~CRenderWindow()
{
    //delete m_Input;
    glfwTerminate();
}

bool CRenderWindow::InitializeWindow(int a_Width, int a_Height, int a_Version_Major, int a_Version_Minor)
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, a_Version_Major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, a_Version_Minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(a_Width, a_Height, "CinkesRenderer", NULL, NULL);
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
    m_Shader = std::make_shared<CShader>("resources/shaders/CShader.vs","resources/shaders/CShader.fss");

    glfwSetWindowUserPointer(m_Window, m_Input.get());

	return true;
}


void CRenderWindow::Run()
{
    while (!glfwWindowShouldClose(m_Window))
    {
        m_Input->ProcessInput(m_Window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!


        for (const auto& current : m_Shapes) {
            // bind textures on corresponding texture units
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, current->GetTexture()->m_Texture);

            // activate shader
            m_Shader->use();
            // render boxes
            glBindVertexArray(current->GetVAO());
            m_Shader->setMat4("projection", m_Input->m_Camera->GetProjectionMatrix());
            m_Shader->setMat4("view", m_Input->m_Camera->GetViewMatrix());    
            m_Shader->setMat4("model", current->GetTransform());
            glm::vec3 position = current->GetTransform()[3];
            //std::cout << position[0] << " " << position[1] << " " << position[2] << std::endl;
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        Update();
        glfwSwapBuffers(m_Window);
        glfwPollEvents();

    }
}

void CRenderWindow::Update()
{
}

bool CRenderWindow::AddRenderShape(std::shared_ptr<CRenderShape>& a_Shape)
{
    auto found = std::find(m_Shapes.begin(), m_Shapes.end(), a_Shape);
    if (found == m_Shapes.end()) {
        m_Shapes.push_back(a_Shape);
        return true;
    }
    
    return false;
}

bool CRenderWindow::RemoveRenderShapeByObject(std::shared_ptr<CRenderShape>& a_Shape)
{
    auto found = std::find(m_Shapes.begin(), m_Shapes.end(), a_Shape);
    if (found != m_Shapes.end()) {
        m_Shapes.erase(found);
        return true;
    }

    return false; 
}

bool CRenderWindow::RemoveRenderShapeByIndex(unsigned int a_Index)
{
    if (a_Index > m_Shapes.size()) {
        auto found = std::find(m_Shapes.begin(), m_Shapes.end(), m_Shapes[a_Index]);
        m_Shapes.erase(found);
   }

    return false;
}
