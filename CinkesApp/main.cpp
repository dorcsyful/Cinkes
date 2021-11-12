#include <filesystem>
#include <memory>
#include <glm/glm/glm.hpp>

#include "Egg/EggRenderer.h"
#include "Egg/InputQueue.h"
#include "Egg/Timer.h"
#include "Egg/Profiler.h"

int main()
{
    using namespace egg;

    RendererSettings settings;
    settings.debugFlags = DebugPrintFlags::ERROR | DebugPrintFlags::WARNING;
    settings.vSync = false;
    settings.clearColor = glm::vec4(0.f, 0.5f, 0.9f, 1.f);
    settings.lockCursor = true;
    settings.m_SwapBufferCount = 3;
    settings.shadersPath = std::filesystem::current_path().parent_path().string() + "/Dependencies/shaders/";

    auto renderer = EggRenderer::CreateInstance(settings);
    Camera camera;
    camera.UpdateProjection(70.f, 0.1f, 600.f, static_cast<float>(settings.resolutionX) / static_cast<float>(settings.resolutionY));

    if (renderer->Init(settings))
    {
		//Create one cube.
		Transform meshTransform;
		meshTransform.Translate({ 0.f, 0.f, 0.f });
		ShapeCreateInfo shapeInfo;
		shapeInfo.m_Radius = 1.f;
		shapeInfo.m_ShapeType = Shape::CUBE;
		shapeInfo.m_InitialTransform = meshTransform.GetTransformation();
		auto mesh = renderer->CreateMesh(shapeInfo);

		//Create one material.
		MaterialCreateInfo materialInfo;
		materialInfo.m_MetallicFactor = 0.0f;
		materialInfo.m_RoughnessFactor = 1.0f;
		materialInfo.m_AlbedoFactor = { 1.f, 1.f, 1.f };
		auto material = renderer->CreateMaterial(materialInfo);

		//Create one light.
		SphereLight light;
		light.SetPosition(5.f, 5.f, 0.f);
		light.SetRadiance(5, 5, 5);
		light.SetRadius(1.f);

		Transform cubeTransform;
		cubeTransform.Translate({ 0, 0, 0 });
		bool run = true;
		while (run) {

			//All frame drawing logic.
			auto drawData = renderer->CreateDrawData();
			auto materialHandle = drawData->AddMaterial(material);
			auto meshHandle = drawData->AddMesh(mesh);
			auto lightHandle = drawData->AddLight(light);
			auto instanceHandle = drawData->AddInstance(cubeTransform.GetTransformation(), materialHandle, 0);
			auto drawCallHandle = drawData->AddDrawCall(meshHandle, &instanceHandle, 1);
			drawData->AddDeferredShadingDrawPass(&drawCallHandle, 1);
			drawData->SetCamera(camera);
			run = renderer->DrawFrame(drawData);

			//All input logic.
			auto input = renderer->QueryInput();
			MouseEvent mEvent;
			KeyboardEvent kEvent;
			while (input.GetNextEvent(mEvent))
			{
				constexpr float mouseDivider = 400.f;
				if (mEvent.action == MouseAction::SCROLL)
				{

				}
				else if (mEvent.action == MouseAction::MOVE_X)
				{
					camera.GetTransform().Rotate(Transform::GetWorldUp(), static_cast<float>(mEvent.value) / -mouseDivider);
				}
				else if (mEvent.action == MouseAction::MOVE_Y)
				{
					camera.GetTransform().Rotate(camera.GetTransform().GetRight(), static_cast<float>(mEvent.value) / -mouseDivider);
				}
				else if (mEvent.action == MouseAction::CLICK)
				{
					std::string mbutton = (mEvent.button == MouseButton::MMB ? "MMB" : mEvent.button == MouseButton::RMB ? "RMB" : "LMB");
					printf("Mouse button clicked: %s.\n", mbutton.c_str());
				}
			}

			constexpr float movementSpeed = 0.01f;
			const auto forwardState = input.GetKeyState(EGG_KEY_W);
			const auto rightState = input.GetKeyState(EGG_KEY_D);
			const auto leftState = input.GetKeyState(EGG_KEY_A);
			const auto backwardState = input.GetKeyState(EGG_KEY_S);
			const auto upState = input.GetKeyState(EGG_KEY_E);
			const auto downState = input.GetKeyState(EGG_KEY_Q);
			if (forwardState != ButtonState::NOT_PRESSED) camera.GetTransform().Translate(camera.GetTransform().GetForward() * -movementSpeed);
			if (rightState != ButtonState::NOT_PRESSED) camera.GetTransform().Translate(camera.GetTransform().GetRight() * movementSpeed);
			if (leftState != ButtonState::NOT_PRESSED) camera.GetTransform().Translate(camera.GetTransform().GetLeft() * movementSpeed);
			if (backwardState != ButtonState::NOT_PRESSED) camera.GetTransform().Translate(camera.GetTransform().GetBack() * -movementSpeed);
			if (upState != ButtonState::NOT_PRESSED) camera.GetTransform().Translate(camera.GetTransform().GetWorldUp() * movementSpeed);
			if (downState != ButtonState::NOT_PRESSED) camera.GetTransform().Translate(camera.GetTransform().GetWorldDown() * movementSpeed);
		}
    }



    if (renderer->CleanUp())
    {
        printf("Renderer successfully cleaned up!\n");
    }
    else
    {
        printf("Could not clean up renderer properly!\n");
    }
	return 0;
}