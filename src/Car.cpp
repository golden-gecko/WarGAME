#include "PCH.hpp"

#include "Car.hpp"

void Car::load()
{
    unload();

    entity = scene->createEntity(name, Ogre::SceneManager::PT_CUBE);
    entity->setUserAny(Ogre::Any(this));
    entity->setMaterialName("Car");

    sceneNode = scene->createSceneNode(name);
    sceneNode->attachObject(entity);
    sceneNode->setUserAny(Ogre::Any(this));
}

void Car::unload()
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

void Car::update(float time)
{
    sceneNode->translate(Ogre::Vector3::UNIT_Z * 1.0f * time);
}
