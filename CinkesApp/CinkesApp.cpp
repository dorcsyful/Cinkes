/*******************************************************************************************
*
*   raylib [core] example - 3d camera first person
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <iostream>

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#define MAX_COLUMNS 20
#include "CBoxShape.h"
#include "CGlue.h"
#include "CPhysicsWorld.h"

using namespace Cinkes;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Test");
    std::shared_ptr<CPhysicsWorld> physicsworld = std::make_shared<CPhysicsWorld>();
    std::unique_ptr<CGlue> glue = std::make_unique<CGlue>(physicsworld.get());
    std::shared_ptr<CBoxShape> boxShape = std::make_shared<CBoxShape>();
    boxShape->SetDimensions(1, 1, 1);
    std::shared_ptr<CCollisionObject> collisionObject = std::make_shared<CCollisionObject>();
    collisionObject->SetCollisionShape(boxShape);
    CTransform trans = CTransform(CMat3x3(), CVector3(0, 10, 1));
    collisionObject->SetTransform(trans);
    physicsworld->AddObject(collisionObject);

    // Define the camera to look into our 3d world (position, target, up vector)
    Camera camera = { { 0.0f, 10.0f, -10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
	SetCameraMode(camera, CAMERA_FIRST_PERSON); // Set a first person camera mode


    SetTargetFPS(60);                           // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())                // Detect window close button or ESC key
    {
        glue->UpdateObjectList();

        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);                  // Update camera
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        for (auto element : glue->GetAllConnectors())
        {
            Model m = *element.second->m_Raylib;
            DrawModel(m, { element.second->m_Raylib->transform.m3, element.second->m_Raylib->transform.m7,
                element.second->m_Raylib->transform.m11 },element.second->m_Raylib->transform.m14 *0.01f, GREEN);
        }


        EndMode3D();

        DrawRectangle(10, 10, 220, 70, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(10, 10, 220, 70, BLUE);

        DrawText("First person camera default controls:", 20, 20, 10, BLACK);
        DrawText("- Move with keys: W, A, S, D", 40, 40, 10, DARKGRAY);
        DrawText("- Mouse move to look around", 40, 60, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
