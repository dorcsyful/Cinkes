#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "CCamera.h"
#include "CShader.h"
#include "CTexture.h"
#include "CRenderWindow.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
    //delete m_Input;
    glfwTerminate();
}

bool Cinkes::CRenderWindow::InitializeWindow()
{
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
    m_Shader.insert(std::pair<const char*, std::shared_ptr<CShader>>("Base", std::make_shared<CShader>()));
    auto pair = std::pair<const char*, std::vector<std::shared_ptr<CRenderShape>>>("Base", std::vector<std::shared_ptr<CRenderShape>>());
    m_Shapes.insert(pair);
    m_Shader.insert(std::pair<const char*, std::shared_ptr<CShader>>("Line", std::make_shared<CShader>(LINE_VERTEX_SHADER, LINE_FRAGMENT_SHADER)));

    glfwSetWindowUserPointer(m_Window, m_Input.get());

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init("#version 130");


    return true;
}


void Cinkes::CRenderWindow::Run()
{

    while (!glfwWindowShouldClose(m_Window))
    {
        // input
        // -----
        m_Input->ProcessInput(m_Window);
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // render
        // ------


        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Render();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (m_Input->m_Camera->m_Wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }

        glm::mat4 projection = glm::perspective(glm::radians(m_Input->m_Camera->m_FOV), static_cast<float>(WIDTH / HEIGHT), 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(m_Input->m_Camera->m_Position, m_Input->m_Camera->m_Position + m_Input->m_Camera->m_Front, m_Input->m_Camera->m_Up);

        for (const auto& shape : m_Shapes)
        {

            // activate shader
            m_Shader[shape.first]->Use();

            // pass projection matrix to shader (note that in this case it could change every frame)
            m_Shader[shape.first]->setMat4("projection", projection);

            // camera/view transformation
            m_Shader[shape.first]->setMat4("view", view);
            // render boxes
            for (auto& current : m_Shapes[shape.first])
            {
                // bind textures on corresponding texture units
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, current->GetTexture()->m_Texture);
                glBindVertexArray(current->GetVAO());

                m_Shader[shape.first]->setMat4("model", current->GetTransform());

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }


        m_Shader["Line"]->Use();
        //glEnable(GL_LINE_SMOOTH);
        glLineWidth(1);

        for (auto& line : m_Lines) {
            m_Shader["Line"]->setMat4("MVP", projection * view);
            m_Shader["Line"]->setVec3("color", line->m_Color);

            glBindVertexArray(line->m_VAO);
            glDrawArrays(GL_LINE_LOOP, 0, 2);
            glBindVertexArray(0);
        }

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }






    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_Window);
    glfwTerminate();

}

void Cinkes::CRenderWindow::Update()
{
}

bool Cinkes::CRenderWindow::AddRenderShape(std::shared_ptr<CRenderShape>& a_Shape)
{

    bool exists = true;
    for (const auto& current : m_Shapes)
    {
        if (current.first != a_Shape->GetShader()) { exists = false; }
        else { exists = true; break; }
    }
    assert(exists);
    m_Shapes[a_Shape->GetShader()].push_back(a_Shape);
    if (a_Shape->GetTexture() == nullptr)
    {
        a_Shape->LoadTexture(BASE_TEXTURE, m_Shader["Base"].get());
    }
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

bool Cinkes::CRenderWindow::AddShader(const char* a_ShaderName, const char* a_VertexPath, const char* a_FragmentPath)
{
    bool add = true;
    for (auto& current : m_Shader)
    {
        if (current.second->m_VertexPath == a_VertexPath) { add = false; }
        if (current.second->m_FragmentPath == a_FragmentPath) { add = false; }
    }
    if (add) {
        m_Shader.insert(std::make_pair<const char*, std::shared_ptr<CShader>>(static_cast<const char*>(a_ShaderName), std::make_shared<CShader>(a_VertexPath, a_FragmentPath)));
    }
    return false;
}
