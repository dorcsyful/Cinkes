#pragma once
#include <memory>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "CVector3.h"
#include "CQuaternion.h"
#include "CCollisionObject.h"

namespace Cinkes
{

	struct COgreConverter
	{
		COgreConverter(const std::shared_ptr<CCollisionObject>& a_Cinkes, Ogre::Entity* a_Ogre)
		{
			m_Cinkes = a_Cinkes;
			m_Ogre = a_Ogre;
			
		}

		void RemoveObject(Ogre::SceneManager* a_SceneManager) const
		{
			Ogre::SceneNode* node = m_Ogre->getParentSceneNode();
			node->detachAllObjects();
			a_SceneManager->destroySceneNode(node->getName());
		}

		Ogre::Vector3 ConvertPosition() const
		{
			return {m_Cinkes->GetTransform().getOrigin()[0], m_Cinkes->GetTransform().getOrigin()[1], m_Cinkes->GetTransform().getOrigin()[2] };
		}
		Ogre::Vector3 ConvertPosition()
		{
			return { m_Cinkes->GetTransform().getOrigin()[0], m_Cinkes->GetTransform().getOrigin()[1], m_Cinkes->GetTransform().getOrigin()[2] };
		}

		Ogre::Quaternion ConvertQuaternion() const
		{
			CQuaternion cinkes = m_Cinkes->GetTransform().getBasis().ToQuaternion();
			return { cinkes[0],cinkes[1],cinkes[2],cinkes[3] };
		}

		Ogre::Quaternion ConvertQuaternion()
		{
			CQuaternion cinkes = m_Cinkes->GetTransform().getBasis().ToQuaternion();
			return { cinkes[0],cinkes[1],cinkes[2],cinkes[3] };
		}

		std::shared_ptr<CCollisionObject> m_Cinkes;
		Ogre::Entity* m_Ogre;
	};
}