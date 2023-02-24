#pragma once
#include <memory>
#include "CCamera.h"

#include <chrono>

namespace Cinkes {

	class CInputHandler
	{
	public:
		CInputHandler() { m_Camera = std::make_shared<CCamera>(); }
		~CInputHandler() = default;

		void AddMouseMovementToQueue(float a_X, float a_Y) { m_MouseMovement[0] = a_X; m_MouseMovement[1] = a_Y; m_Update[0] = true; }
		void AddMouseScrollToQueue(float a_Y) { m_MouseScroll = a_Y; m_Update[1] = true; }
		void ProcessInput(GLFWwindow* window) {

			float currentFrame = static_cast<float>(glfwGetTime());
			float deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
			if (m_Update[0]) {
				m_Camera->ProcessMouseMovement(m_MouseMovement[0], m_MouseMovement[1]);
				m_Update[0] = false;
			}
			if (m_Update[1]) {
				m_Camera->ProcessMouseScroll(m_MouseScroll);
				m_Update[1] = false;
			}
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				m_Camera->ProcessKeyboard(E_CAMERAMOVEMENT_FORWARD, deltaTime);
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				m_Camera->ProcessKeyboard(E_CAMERAMOVEMENT_BACKWARD, deltaTime);
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				m_Camera->ProcessKeyboard(E_CAMERAMOVEMENT_LEFT, deltaTime);
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				m_Camera->ProcessKeyboard(E_CAMERAMOVEMENT_RIGHT, deltaTime);
			if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
				m_Camera->Wireframe = !m_Camera->Wireframe;

			static auto last_time = std::chrono::system_clock::from_time_t(0);
			auto now = std::chrono::system_clock::now();
			auto passed = now - last_time;
			auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(passed).count();

			if (millis > 100) {
				if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
					m_Camera->index += 1;
					last_time = now;
				}
				if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
				{
					m_Camera->index -= 1;
					last_time = now;
				}

			}
		}
		bool m_Update[2] = { false, false };
		float m_MouseMovement[2] = { 0, 0 };
		float m_MouseScroll{};
		std::shared_ptr<CCamera> m_Camera;
		bool firstMouse = true;
		float lastX{};
		float lastY{};
		float lastFrame{};
	};
};

