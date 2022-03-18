#pragma once
#include <OgreApplicationContext.h>

#include <OgreRoot.h>
#include <OgreEntity.h>
#include <OgreRenderWindow.h>

namespace Cinkes
{
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
			SceneNode* lightNode = m_SceneManager->getRootSceneNode()->createChildSceneNode();
			lightNode->setPosition(20, 200, 50);
			lightNode->attachObject(light);

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
			SceneNode* camNode = m_SceneManager->getRootSceneNode()->createChildSceneNode();
			camNode->setPosition(0, 0, 300);
			camNode->lookAt(Vector3(0, 0, -1), Node::TS_PARENT);
			// create the camera
			Camera* cam = m_SceneManager->createCamera("MainCamera");
			cam->setNearClipDistance(5); // specific to this sample
			cam->setAutoAspectRatio(true);
			camNode->attachObject(cam);
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


		bool m_Go = true;
		SceneManager* m_SceneManager = nullptr;
		RTShader::ShaderGenerator* m_ShaderGenerator = nullptr;
	};

}