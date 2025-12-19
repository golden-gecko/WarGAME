#include "PCH.hpp"

#include "Rectangle.hpp"

namespace Debug
{
	void Rectangle::load()
	{
		unload();

        entity = scene->createEntity(name, Ogre::SceneManager::PT_PLANE);
        entity->setMaterialName("Debug");
        entity->setUserAny(Ogre::Any(this));

		sceneNode = scene->createSceneNode(name);
        sceneNode->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);
        sceneNode->setPosition(Ogre::Vector3(50.0f, 0.1f, 50.0f));
        sceneNode->setScale(Ogre::Vector3::UNIT_SCALE * 0.005f * 100.0f);
		sceneNode->attachObject(entity);
		sceneNode->setUserAny(Ogre::Any(this));

        /*
        sceneNode = scene->createSceneNode(name);
        sceneNode->setDirection(Ogre::Vector3::UNIT_Y, Ogre::Node::TS_LOCAL, Ogre::Vector3::UNIT_Z);
        sceneNode->setPosition(Ogre::Vector3(50.0f, 0.1f, 50.0f));
        sceneNode->setScale(Ogre::Vector3::UNIT_SCALE * 0.005f * size);
		sceneNode->attachObject(entity);
		sceneNode->setUserAny(Ogre::Any(this));
        //*/
	}
    
	void Rectangle::unload()
	{
		if (entity)
		{
			scene->destroyEntity(entity);
		}
    
		if (sceneNode)
		{
			scene->destroySceneNode(sceneNode);
		}

		entity = NULL;
		sceneNode = NULL;
	}
}
