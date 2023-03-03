#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include "CCameraSettings.h"
#include "CRenderDefines.h"
// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods


namespace Cinkes {
    // An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL

    enum E_CAMERAMOVEMENT {
        E_CAMERAMOVEMENT_FORWARD,
        E_CAMERAMOVEMENT_BACKWARD,
        E_CAMERAMOVEMENT_LEFT,
        E_CAMERAMOVEMENT_RIGHT
    };

    class CCamera
    {
    public:
        // camera Attributes
        glm::vec3 m_Position{};
        glm::vec3 m_Front{};
        glm::vec3 m_Up{};
        glm::vec3 m_Right{};
        glm::vec3 m_WorldUp{};
        int m_Index{};
        // euler Angles
        float m_Yaw;
        float m_Pitch;
        // camera options
        float m_MovementSpeed;
        float m_MouseSensitivity;
        float m_Zoom;
        float m_FOV{};
        bool m_Wireframe{};

        // constructor with vectors
        CCamera() {
            m_Wireframe = false;
            // camera Attributes
            CCameraSettings a_Settings = CCameraSettings();
            m_Position = glm::vec3(10.0, 0.0, 0.0);
            m_Front = glm::vec3(1.0, 0.0, 1.0);
            m_WorldUp = a_Settings.WorldUp;
            // euler Angles
            m_Yaw = 90;
            m_Pitch = 0;
            // camera options
            m_MovementSpeed = a_Settings.MovementSpeed;
            m_MouseSensitivity = a_Settings.MouseSensitivity;
            m_Zoom = a_Settings.Zoom;
            m_Index = 0;
            m_FOV = 45.f;
            updateCameraVectors();
        }

        CCamera(const CCameraSettings& a_Settings)
        {
            // camera Attributes
            m_Position = a_Settings.Position;
            m_Front = a_Settings.Front;
            m_WorldUp = a_Settings.WorldUp;
            // euler Angles
            m_Yaw = a_Settings.Yaw;
            m_Pitch = a_Settings.Pitch;
            m_Index = 0;
            // camera options
            m_MovementSpeed = a_Settings.MovementSpeed;
            m_MouseSensitivity = a_Settings.MouseSensitivity;
            m_Zoom = a_Settings.Zoom;
            updateCameraVectors();
        }
        // constructor with scalar values
        CCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
            : m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(7.f), m_MouseSensitivity(0.1f), m_Zoom(45.f)
        {
            m_Position = glm::vec3(posX, posY, posZ);
            m_WorldUp = glm::vec3(upX, upY, upZ);
            m_Yaw = yaw;
            m_Pitch = pitch;
            updateCameraVectors();
        }

        // returns the view matrix calculated using Euler Angles and the LookAt Matrix
        glm::mat4 GetViewMatrix()
        {
            return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
        }

        glm::mat4 GetProjectionMatrix()
        {
            return glm::perspective(glm::radians(70.f), static_cast<float>(WIDTH / HEIGHT), 0.1f, 100.0f);;
        }

        // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
        void ProcessKeyboard(E_CAMERAMOVEMENT a_Direction, float a_DeltaTime)
        {
            float velocity = m_MovementSpeed * a_DeltaTime;
            if (a_Direction == E_CAMERAMOVEMENT_FORWARD)
                m_Position += m_Front * velocity;
            if (a_Direction == E_CAMERAMOVEMENT_BACKWARD)
                m_Position -= m_Front * velocity;
            if (a_Direction == E_CAMERAMOVEMENT_LEFT)
                m_Position -= m_Right * velocity;
            if (a_Direction == E_CAMERAMOVEMENT_RIGHT)
                m_Position += m_Right * velocity;
        }

        // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
        void ProcessMouseMovement(float a_Xoffset, float a_Yoffset, GLboolean a_ConstrainPitch = true)
        {
            a_Xoffset *= m_MouseSensitivity;
            a_Yoffset *= m_MouseSensitivity;

            m_Yaw += a_Xoffset;
            m_Pitch += a_Yoffset;

            // make sure that when pitch is out of bounds, screen doesn't get flipped
            if (a_ConstrainPitch)
            {
                if (m_Pitch > 89.0f)
                    m_Pitch = 89.0f;
                if (m_Pitch < -89.0f)
                    m_Pitch = -89.0f;
            }

            // update Front, Right and Up Vectors using the updated Euler angles
            updateCameraVectors();
        }

        // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
        void ProcessMouseScroll(float a_Yoffset)
        {
            m_Zoom -= (float)a_Yoffset;
            if (m_Zoom < 1.0f)
                m_Zoom = 1.0f;
            if (m_Zoom > 45.0f)
                m_Zoom = 45.0f;
        }

    private:
        // calculates the front vector from the Camera's (updated) Euler Angles
        void updateCameraVectors()
        {
            // calculate the new Front vector
            glm::vec3 front{};
            front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
            front.y = sin(glm::radians(m_Pitch));
            front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
            m_Front = glm::normalize(front);
            // also re-calculate the Right and Up vector
            m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            m_Up = glm::normalize(glm::cross(m_Right, m_Front));
        }
    };
};
#endif