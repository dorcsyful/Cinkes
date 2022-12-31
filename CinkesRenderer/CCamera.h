#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include "CCameraSettings.h"
// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum CCamera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

namespace Cinkes {
    // An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
    class CCamera
    {
    public:
        // camera Attributes
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
        // euler Angles
        float Yaw;
        float Pitch;
        // camera options
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

        // constructor with vectors
        CCamera() {
            // camera Attributes
            CCameraSettings a_Settings = CCameraSettings();
            Position = a_Settings.Position;
            Front = a_Settings.Front;
            WorldUp = a_Settings.WorldUp;
            // euler Angles
            Yaw = a_Settings.Yaw;
            Pitch = a_Settings.Pitch;
            // camera options
            MovementSpeed = a_Settings.MovementSpeed;
            MouseSensitivity = a_Settings.MouseSensitivity;
            Zoom = a_Settings.Zoom;
            updateCameraVectors();
        }

        CCamera(const CCameraSettings& a_Settings)
        {
            // camera Attributes
            Position = a_Settings.Position;
            Front = a_Settings.Front;
            WorldUp = a_Settings.WorldUp;
            // euler Angles
            Yaw = a_Settings.Yaw;
            Pitch = a_Settings.Pitch;
            // camera options
            MovementSpeed = a_Settings.MovementSpeed;
            MouseSensitivity = a_Settings.MouseSensitivity;
            Zoom = a_Settings.Zoom;
            updateCameraVectors();
        }
        // constructor with scalar values
        CCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
            : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(2.5), MouseSensitivity(0.1), Zoom(45)
        {
            Position = glm::vec3(posX, posY, posZ);
            WorldUp = glm::vec3(upX, upY, upZ);
            Yaw = yaw;
            Pitch = pitch;
            updateCameraVectors();
        }

        // returns the view matrix calculated using Euler Angles and the LookAt Matrix
        glm::mat4 GetViewMatrix()
        {
            return glm::lookAt(Position, Position + Front, Up);
        }

        glm::mat4 GetProjectionMatrix()
        {
            return glm::perspective(glm::radians(45.f), (float)800 / (float)600, 0.1f, 100.0f);;
        }

        // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
        void ProcessKeyboard(CCamera_Movement direction, float deltaTime)
        {
            float velocity = MovementSpeed * deltaTime;
            if (direction == FORWARD)
                Position += Front * velocity;
            if (direction == BACKWARD)
                Position -= Front * velocity;
            if (direction == LEFT)
                Position -= Right * velocity;
            if (direction == RIGHT)
                Position += Right * velocity;
        }

        // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
        {
            xoffset *= MouseSensitivity;
            yoffset *= MouseSensitivity;

            Yaw += xoffset;
            Pitch += yoffset;

            // make sure that when pitch is out of bounds, screen doesn't get flipped
            if (constrainPitch)
            {
                if (Pitch > 89.0f)
                    Pitch = 89.0f;
                if (Pitch < -89.0f)
                    Pitch = -89.0f;
            }

            // update Front, Right and Up Vectors using the updated Euler angles
            updateCameraVectors();
        }

        // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
        void ProcessMouseScroll(float yoffset)
        {
            Zoom -= (float)yoffset;
            if (Zoom < 1.0f)
                Zoom = 1.0f;
            if (Zoom > 45.0f)
                Zoom = 45.0f;
        }

    private:
        // calculates the front vector from the Camera's (updated) Euler Angles
        void updateCameraVectors()
        {
            // calculate the new Front vector
            glm::vec3 front;
            front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            front.y = sin(glm::radians(Pitch));
            front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            Front = glm::normalize(front);
            // also re-calculate the Right and Up vector
            Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            Up = glm::normalize(glm::cross(Right, Front));
        }
    };
};
#endif