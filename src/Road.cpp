#include "PCH.hpp"

#include "Road.hpp"

void Road::load()
{
    unload();

    entity = scene->createEntity(name, Ogre::SceneManager::PT_PLANE);
    entity->setUserAny(Ogre::Any(this));
    entity->setMaterialName("Road");

    sceneNode = scene->createSceneNode(name);
    sceneNode->attachObject(entity);
    sceneNode->setUserAny(Ogre::Any(this));
    sceneNode->setScale(Ogre::Vector3::UNIT_SCALE * 0.005f);
    sceneNode->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);
}

void Road::unload()
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
