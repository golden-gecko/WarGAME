#include "PCH.hpp"

#include "Industrial.hpp"

void Industrial::load()
{
    unload();

    entity = scene->createEntity(name, Ogre::SceneManager::PT_CUBE);
    entity->setUserAny(Ogre::Any(this));
    entity->setMaterialName("Industrial");

    sceneNode = scene->createSceneNode(name);
    sceneNode->attachObject(entity);
    sceneNode->setUserAny(Ogre::Any(this));

    setSize(Ogre::Vector3::UNIT_SCALE * 10.0f);
    setPosition(Ogre::Vector3::ZERO);

    workers = 30 + rand() % 30;
}

void Industrial::unload()
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
