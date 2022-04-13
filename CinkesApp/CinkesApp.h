#pragma once
#include <iostream>
#include <OgreApplicationContext.h>

#include <OgreRoot.h>
#include <OgreEntity.h>
#include <OgreRenderWindow.h>

#include "CCollisionObject.h"
#include "CCollisionShape.h"
#include "COgreConverter.h"
#include "CPhysicsWorld.h"

namespace Cinkes
{
	class CRigidBody;
	class CPhysicsWorld;
	using namespace Ogre;
	using namespace OgreBites;

	class CinkesApp : public ApplicationContext, public InputListener
	{
	public:
		CinkesApp() = default;

		bool keyPressed(const KeyboardEvent& a_Event) override
		{
			if (a_Event.keysym.sym == SDLK_ESCAPE)
			{
				getRoot()->queueEndRendering();
				m_Go = false;
			}
			return true;
		}

		void CreateSkybox(const std::string& a_Name) const {
			m_SceneManager->setSkyBox(true, a_Name);
		}

		void CreateSceneManager()
		{
			m_SceneManager = getRoot()->createSceneManager();

			// register our scene with the RTSS
			m_ShaderGenerator = RTShader::ShaderGenerator::getSingletonPtr();
			m_ShaderGenerator->addSceneManager(m_SceneManager);
		}

		void CreateBasicLights() const
		{
			Light* light = m_SceneManager->createLight("MainLight");
			SceneNode* light_node = m_SceneManager->getRootSceneNode()->createChildSceneNode();
			light_node->setPosition(20, 200, 50);
			light_node->attachObject(light);

			Light* l = m_SceneManager->createLight();
			l->setType(Light::LT_DIRECTIONAL);
			l->setDiffuseColour(ColourValue::White);
			l->setSpecularColour(ColourValue(0.4f, 0.4f, 0.4f));
			SceneNode* ln = m_SceneManager->getRootSceneNode()->createChildSceneNode();
			ln->setDirection(Vector3(0.0, -0.1f, 0.0).normalisedCopy());
			ln->attachObject(l);
		}

		void CreateCamera() const
		{
			SceneNode* cam_node = m_SceneManager->getRootSceneNode()->createChildSceneNode();
			cam_node->setPosition(0, 0, 300);
			cam_node->lookAt(Vector3(0, 0, -1), Node::TS_PARENT);
			// create the camera
			Camera* cam = m_SceneManager->createCamera("MainCamera");
			cam->setNearClipDistance(5); // specific to this sample
			cam->setAutoAspectRatio(true);
			cam_node->attachObject(cam);
			// and tell it to render into the main window
			getRenderWindow()->addViewport(cam);
		}

		void setup() override
		{
			// do not forget to call the base first
			ApplicationContext::setup();
			addInputListener(this);

			CreateSceneManager();
			CreateBasicLights();
			CreateSkybox("Examples/CloudyNoonSkyBox");
			CreateCamera();
		}

		bool AddObject(const std::shared_ptr<CCollisionObject>& a_Cinkes,
			const std::string& a_MeshName = "cube.mesh", const std::string& a_MaterialName = "Ogre/Compositor/OldMovie")
		{
			for (auto& converter : m_Converters)
			{
				if (a_Cinkes == converter->m_Cinkes) { return false; }
			}
			Ogre::Entity* entity = m_SceneManager->createEntity(a_MeshName);
			entity->setMaterialName(a_MaterialName);
			auto node = m_SceneManager->getRootSceneNode()->createChildSceneNode();
			node->attachObject(entity);
			auto aabb = entity->getBoundingBox();

			std::shared_ptr<COgreConverter> temp = std::make_shared<COgreConverter>(a_Cinkes, entity);
			m_Converters.push_back(temp);
			m_PhysicsWorld->AddRigidBody(std::static_pointer_cast<CRigidBody>(a_Cinkes));
			return true;
		}

		void Convert() const
		{
			for (auto& current : m_Converters)
			{
				current->m_Ogre->getParentSceneNode()->setPosition(current->ConvertPosition());
				current->m_Ogre->getParentSceneNode()->setOrientation(current->ConvertQuaternion());
			}
		}


		bool m_Go = true;
		SceneManager* m_SceneManager = nullptr;
		RTShader::ShaderGenerator* m_ShaderGenerator = nullptr;
		std::vector<std::shared_ptr<COgreConverter>> m_Converters;
		CPhysicsWorld* m_PhysicsWorld = nullptr;
	};

}
