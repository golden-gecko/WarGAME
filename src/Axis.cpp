#include "PCH.hpp"

#include "Axis.hpp"

namespace Debug
{
	void Axis::load()
	{
		unload();

		manualObject = scene->createManualObject(name);
		manualObject->setCastShadows(false);
		manualObject->setUserAny(Ogre::Any(this));

		manualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
    
		manualObject->position(0.0f, 0.0f, 0.0f);
		manualObject->colour(Ogre::ColourValue::Red);

		manualObject->position(1.0f, 0.0f, 0.0f);
		manualObject->colour(Ogre::ColourValue::Red);
    
		manualObject->position(0.0f, 0.0f, 0.0f);
		manualObject->colour(Ogre::ColourValue::Green);

		manualObject->position(0.0f, 1.0f, 0.0f);
		manualObject->colour(Ogre::ColourValue::Green);
    
		manualObject->position(0.0f, 0.0f, 0.0f);
		manualObject->colour(Ogre::ColourValue::Blue);

		manualObject->position(0.0f, 0.0f, 1.0f);
		manualObject->colour(Ogre::ColourValue::Blue);

		manualObject->end();

		sceneNode = scene->createSceneNode(name);
		sceneNode->setPosition(Ogre::Vector3::ZERO);
		sceneNode->setScale(Ogre::Vector3::UNIT_SCALE * 100.0f);
		sceneNode->attachObject(manualObject);
		sceneNode->setUserAny(Ogre::Any(this));
	}

	void Axis::unload()
	{
		if (manualObject)
		{
			scene->destroyManualObject(manualObject);
		}
    
		if (sceneNode)
		{
			scene->destroySceneNode(sceneNode);
		}

		manualObject = NULL;
		sceneNode = NULL;
	}
}
