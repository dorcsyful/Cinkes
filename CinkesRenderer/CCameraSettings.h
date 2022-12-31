#pragma once
#include "CScalar.h"
#include "glm/glm.hpp"
namespace Cinkes {
	struct CCameraSettings
	{
	public:
		//initializes with default values
		CCameraSettings(const glm::vec3& a_Position = glm::vec3(0, 0, 0), const glm::vec3& a_Front = glm::vec3(0, 0, -1),
			const glm::vec3& a_Up = glm::vec3(0, 1, 0), CScalar a_Yaw = -90, CScalar a_Pitch = 0, CScalar a_Speed = 2.5,
			CScalar a_Sensitivity = 0.1, CScalar a_Zoom = 45) 
		{
			glm::vec3 Position = a_Position;
			glm::vec3 Front = a_Front;
			glm::vec3 WorldUp = a_Up;
			// euler Angles
			CScalar Yaw = a_Yaw;
			CScalar Pitch = a_Pitch;
			// camera options
			CScalar MovementSpeed = a_Speed;
			CScalar MouseSensitivity = a_Sensitivity;
			CScalar Zoom = a_Zoom;
		}

		glm::vec3 Position = glm::vec3(0,0,0);
		glm::vec3 Front = glm::vec3(0, 0, -1);
		glm::vec3 WorldUp = glm::vec3(0, 1, 0);
		// euler Angles
		CScalar Yaw = -90;
		CScalar Pitch = 0;
		// camera options
		CScalar MovementSpeed = 2.5;
		CScalar MouseSensitivity = 0.1;
		CScalar Zoom = 45;

	};
};