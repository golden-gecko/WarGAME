#include "PCH.hpp"

#include "Structure.hpp"

void Structure::load()
{
    unload();

    entity = scene->createEntity(name, Ogre::SceneManager::PT_CUBE);
    entity->setUserAny(Ogre::Any(this));
    entity->setMaterialName("Structure");

    sceneNode = scene->createSceneNode(name);
    sceneNode->attachObject(entity);
    sceneNode->setUserAny(Ogre::Any(this));

    setSize(Ogre::Vector3::UNIT_SCALE * 10.0f);
    setPosition(Ogre::Vector3::ZERO);
}

void Structure::unload()
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
