#pragma once

#include "PCH.hpp"

class Scene;

#include "Object.hpp"

class Scene
{
public:
    Scene(const std::string& name) : name(name), sceneManager(NULL)
    {
    }

    virtual ~Scene()
    {
    }

    virtual void load();

    virtual void unload();

    virtual void update(float time);

    Ogre::Camera* createCamera(const std::string& name);

    Ogre::Entity* createEntity(const std::string& name, const std::string& meshName)
    {
        return sceneManager->createEntity(name, meshName);
    }

    Ogre::Entity* createEntity(const std::string& name, Ogre::SceneManager::PrefabType type)
    {
        return sceneManager->createEntity(name, type);
    }

    Ogre::ManualObject* createManualObject(const std::string& name)
    {
        return sceneManager->createManualObject(name);
    }

    Ogre::SceneNode* createSceneNode(const std::string& name = "")
    {
        return sceneManager->getRootSceneNode()->createChildSceneNode(name);
    }
    
    void destroyEntity(Ogre::Entity* entity)
    {
        sceneManager->destroyEntity(entity);
    }

    void destroyManualObject(Ogre::ManualObject* manualObject)
    {
        sceneManager->destroyManualObject(manualObject);
    }

    void destroySceneNode(Ogre::SceneNode* sceneNode)
    {
        sceneManager->destroySceneNode(sceneNode);
    }

    const std::string& getName() const
    {
        return name;
    }
protected:
    std::string name;
    
    Ogre::SceneManager* sceneManager;

    std::map<std::string, Object*> objects;
};
