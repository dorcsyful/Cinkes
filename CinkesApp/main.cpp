#include <filesystem>
#include <iostream>
#include <memory>
#include <glm/glm/glm.hpp>

#include "Egg/EggRenderer.h"
#include "Egg/InputQueue.h"

#include "../CinkesMath/CVector3.h"
#include "../CinkesMath/CQuaternion.h"
#include "../CinkesMath/CMat3x3.h"
#include "../CinkesCollision/CCollisionWorld.h"
#include "../CinkesCollision/CCollisionShape.h"
#include "../CinkesCollision/CBoxShape.h"
#include "../CinkesCollision/CBVH.h"
#include "../CinkesCollision/CContactInfo.h"
struct CinkesToEgg
{
	std::shared_ptr<Cinkes::CCollisionObject> m_Cinkes;
	std::shared_ptr<egg::EggStaticMesh> m_Egg;
	std::shared_ptr<egg::EggMaterial> m_Material;
	glm::mat4x4 m_Transform{};
};

CinkesToEgg CreateObject(const std::shared_ptr<Cinkes::CCollisionWorld>& a_World, const std::shared_ptr<Cinkes::CBoxShape>& a_Shape,
						egg::EggRenderer* a_Renderer, const std::shared_ptr<egg::EggMaterial>& a_Material)
{
	CinkesToEgg returnValue;

	std::shared_ptr<Cinkes::CCollisionObject> collisionObject = std::make_shared<Cinkes::CCollisionObject>();
	std::shared_ptr<Cinkes::CCollisionShape> meow = std::static_pointer_cast<Cinkes::CCollisionShape>(a_Shape);
	collisionObject->SetCollisionShape(meow);
	Cinkes::CTransform cTransform = Cinkes::CTransform();
	cTransform.setOrigin(Cinkes::CVector3(2, 2, 2));
	collisionObject->SetTransform(cTransform);
	a_World->AddObject(collisionObject);
	returnValue.m_Cinkes = collisionObject;

	//Create one cube.
	egg::Transform meshTransform;
	meshTransform.Translate({ 2.f, 2.f, 2.f });
	egg::ShapeCreateInfo shapeInfo;
	shapeInfo.m_Radius = 1.f;
	shapeInfo.m_ShapeType = egg::Shape::CUBE;
	//shapeInfo.m_InitialTransform = meshTransform.GetTransformation();
	returnValue.m_Egg = a_Renderer->CreateMesh(shapeInfo);

	returnValue.m_Material = a_Material;

	Cinkes::CMat3x3 mat = collisionObject->GetTransform().getBasis();
	returnValue.m_Transform = meshTransform.GetTransformation();

	return returnValue;
}

bool HandleInput(egg::Camera& a_Camera, egg::EggRenderer* a_Renderer, Cinkes::CVector3& a_CameraRotation)
{
	//All input logic.
	auto input = a_Renderer->QueryInput();
	egg::MouseEvent mEvent;
	
	while (input.GetNextEvent(mEvent))
	{
		constexpr float mouseDivider = 20.f;
		if (mEvent.action == egg::MouseAction::SCROLL)
		{

		}
		else if (mEvent.action == egg::MouseAction::MOVE_X)
		{
			auto value = static_cast<float>(mEvent.value) / -mouseDivider;
			value = a_CameraRotation.getY() + value;
			value -= ((int)value / 360) * 360;
			a_CameraRotation.setY(value);
		}
		else if (mEvent.action == egg::MouseAction::MOVE_Y)
		{
			auto value = static_cast<float>(mEvent.value) / -mouseDivider;
			value = a_CameraRotation.getX() + value;
			if(value > 179)
			{
				value = 179;
			}
			else if (value < 1) value = 1;
			a_CameraRotation.setX(value);
		}
		else if (mEvent.action == egg::MouseAction::CLICK)
		{
			std::string mbutton = (mEvent.button == egg::MouseButton::MMB ? "MMB" : mEvent.button == egg::MouseButton::RMB ? "RMB" : "LMB");
			printf("Mouse button clicked: %s.\n", mbutton.c_str());
		}

		//Update the camera rotation.
		a_Camera.GetTransform().SetRotation(a_Camera.GetTransform().GetUp(), 0.f);
		a_Camera.GetTransform().Rotate(a_Camera.GetTransform().GetUp(), a_CameraRotation.getY() * (3.141592f / 180.f));
		a_Camera.GetTransform().Rotate(a_Camera.GetTransform().GetRight(), (-3.141592f / 2.f) + a_CameraRotation.getX() * (3.141592f / 180.f));
	}

	egg::KeyboardEvent kEvent;
	while(input.GetNextEvent(kEvent))
	{
	    if(kEvent.keyCode == EGG_KEY_ESCAPE)
	    {
			return false;
	    }
	}

	constexpr float movementSpeed = 0.01f;
	const auto forwardState = input.GetKeyState(EGG_KEY_W);
	const auto rightState = input.GetKeyState(EGG_KEY_D);
	const auto leftState = input.GetKeyState(EGG_KEY_A);
	const auto backwardState = input.GetKeyState(EGG_KEY_S);
	const auto upState = input.GetKeyState(EGG_KEY_E);
	const auto downState = input.GetKeyState(EGG_KEY_Q);
	if (forwardState != egg::ButtonState::NOT_PRESSED) a_Camera.GetTransform().Translate(a_Camera.GetTransform().GetForward() * -movementSpeed);
	if (rightState != egg::ButtonState::NOT_PRESSED) a_Camera.GetTransform().Translate(a_Camera.GetTransform().GetRight() * movementSpeed);
	if (leftState != egg::ButtonState::NOT_PRESSED) a_Camera.GetTransform().Translate(a_Camera.GetTransform().GetLeft() * movementSpeed);
	if (backwardState != egg::ButtonState::NOT_PRESSED) a_Camera.GetTransform().Translate(a_Camera.GetTransform().GetBack() * -movementSpeed);
	if (upState != egg::ButtonState::NOT_PRESSED) a_Camera.GetTransform().Translate(a_Camera.GetTransform().GetWorldUp() * movementSpeed);
	if (downState != egg::ButtonState::NOT_PRESSED) a_Camera.GetTransform().Translate(a_Camera.GetTransform().GetWorldDown() * movementSpeed);

	return true;
}

int main()
{
	using namespace Cinkes;
	using namespace egg;

	std::shared_ptr<Cinkes::CBoxShape> collisionShape = std::make_shared<Cinkes::CBoxShape>();
	collisionShape->SetDimensions(0.5f, 0.5f, 0.5f);
	std::shared_ptr collisionWorld = std::make_unique<Cinkes::CCollisionWorld>();



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

	CVector3 cameraRotation = CVector3(0, 0, 0);

	if (renderer->Init(settings))
	{
		std::vector<CinkesToEgg> objects;


		//Create one material.
		MaterialCreateInfo materialInfo;
		materialInfo.m_MetallicFactor = 0.0f;
		materialInfo.m_RoughnessFactor = 1.0f;
		materialInfo.m_AlbedoFactor = { 1.f, 0.f, 0.f };
		auto material = renderer->CreateMaterial(materialInfo);

		MaterialCreateInfo hitmaterialInfo;
		hitmaterialInfo.m_MetallicFactor = 0.0f;
		hitmaterialInfo.m_RoughnessFactor = 1.0f;
		hitmaterialInfo.m_AlbedoFactor = { 0.f, 1.f, 0.f };
		auto hitmaterial = renderer->CreateMaterial(hitmaterialInfo);

		MaterialCreateInfo narrowmaterialInfo;
		narrowmaterialInfo.m_MetallicFactor = 0.0f;
		narrowmaterialInfo.m_RoughnessFactor = 1.0f;
		narrowmaterialInfo.m_AlbedoFactor = { 0.f, 0.f, 1.f };
		auto narrowmaterial = renderer->CreateMaterial(narrowmaterialInfo);

		//Create one light.
		SphereLight light;
		light.SetPosition(5.f, 100.f, 0.f);
		light.SetRadiance(10, 10, 10);
		light.SetRadius(50.f);

		Transform cubeTransform;

		bool run = true;

		objects.push_back(CreateObject(collisionWorld, collisionShape, renderer.get(), material));
		objects.push_back(CreateObject(collisionWorld, collisionShape, renderer.get(), material));
		glm::quat q = glm::quat(0.732759f, 0.4618481f, 0.1909372f, 0.4618481f);
		cubeTransform.SetRotation(q);
		cubeTransform.SetTranslation({ 2.f, 3, 2 });
		objects[1].m_Transform = cubeTransform.GetTransformation();
		objects[1].m_Cinkes->GetTransform().setOrigin(Cinkes::CVector3(2.f, 3.f, 2));
		auto mat = Cinkes::CMat3x3(Cinkes::CVector3(0.678701, 0.2805885, 0.678701), 1.4968576);
		objects[1].m_Cinkes->GetTransform().setBasis(mat);



		collisionWorld->RunCollision(1);
		std::vector<std::shared_ptr<Cinkes::CContactInfo>> narrow;
		std::vector<std::shared_ptr<Cinkes::CBroadContactInfo>> broad;
		collisionWorld->getContacts(narrow, broad);

		for(auto& current : objects)
		{
			for (auto& broad1 : broad)
			{
				for(auto& element : broad1->m_Objects)
				{
					if (current.m_Cinkes.get() == element.get()) { current.m_Material = hitmaterial; break; }
				}
			}
		}

		for (auto& object : narrow)
		{
			for (auto& current : objects)
			{
				if(current.m_Cinkes.get() == object->m_First.get() || current.m_Cinkes.get() == object->m_Second.get())
				{
					current.m_Material = narrowmaterial;
					std::cout << "Current collision normal: ";
					std::cout << object->m_Normal.getX() << " " << object->m_Normal.getY() << " " << object->m_Normal.getZ() << "\n";
					std::cout << "Current contact points: ";
					for (auto& points : object->m_ContactPoints)
					{
						std::cout << points.getX() << " " << points.getY() << " " << points.getZ() << "\n";
					}
				}
			}
		}
		
		//LOOP
		while (run) {

			EggRenderer* renderpointer = renderer.get();
			run = HandleInput(camera, renderpointer, cameraRotation);

			//All frame drawing logic.
			auto drawData = renderer->CreateDrawData();
			MaterialHandle materialHandle;
			auto regularMaterialHandle = drawData->AddMaterial(material);
			auto hitMaterialHandle = drawData->AddMaterial(hitmaterial);
			auto narrowMaterialHandle = drawData->AddMaterial(narrowmaterial);
			drawData->AddLight(light);
			

			std::vector<InstanceDataHandle> instanceDataHandlesandles;
			std::vector<DrawCallHandle> drawCallHandles;
				auto meshHandle = drawData->AddMesh(objects[0].m_Egg);


			for (auto& current: objects) 
			{
				if (current.m_Material == hitmaterial)
				{
					materialHandle = hitMaterialHandle;
				}
				else if(current.m_Material == narrowmaterial)
				{
					materialHandle = narrowMaterialHandle;
				}
				else { materialHandle = regularMaterialHandle; }
				auto instanceHandle = drawData->AddInstance(current.m_Transform, materialHandle, 0);
				instanceDataHandlesandles.push_back(instanceHandle);
			}

			auto drawCallHandle = drawData->AddDrawCall(meshHandle, instanceDataHandlesandles.data(), instanceDataHandlesandles.size());

			drawCallHandles.push_back(drawCallHandle);
			drawData->AddDeferredShadingDrawPass(drawCallHandles.data(), drawCallHandles.size());
			drawData->SetCamera(camera);
			run = renderer->DrawFrame(drawData) && run;
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

