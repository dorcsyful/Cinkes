#pragma once
#include "glm/glm.hpp"
namespace Cinkes {
	struct CCameraSettings
	{
	public:
		//initializes with default values
		CCameraSettings(const glm::vec3& a_Position = glm::vec3(0, 0, -50), const glm::vec3& a_Front = glm::vec3(0, 0, 1),
			const glm::vec3& a_Up = glm::vec3(0, 1, 0), float a_Yaw = -90, float a_Pitch = 0, float a_Speed = 20,
			float a_Sensitivity = 0.8, float a_Zoom = 90) 
		{
			glm::vec3 Position = a_Position;
			glm::vec3 Front = a_Front;
			glm::vec3 WorldUp = a_Up;
			// euler Angles
			float Yaw = a_Yaw;
			float Pitch = a_Pitch;
			// camera options
			float MovementSpeed = a_Speed;
			float MouseSensitivity = a_Sensitivity;
			float Zoom = a_Zoom;
		}

		glm::vec3 Position = glm::vec3(0,0,0);
		glm::vec3 Front = glm::vec3(0, 0, -1);
		glm::vec3 WorldUp = glm::vec3(0, 1, 0);
		// euler Angles
		float Yaw = -90;
		float Pitch = 0;
		// camera options
		float MovementSpeed = 20;
		float MouseSensitivity = 0.1;
		float Zoom = 45;

	};
};