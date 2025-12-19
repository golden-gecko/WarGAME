#pragma once

#include "PCH.hpp"

#include "Object.hpp"
#include "Road.hpp"

class Structure : public Object
{
public:
    Structure(const std::string& name, Scene* scene) : Object(name, scene), entity(NULL), sceneNode(NULL), nearestRoad(NULL)
    {
    }

    virtual void load();

    virtual void unload();

    void setPosition(const Ogre::Vector3& position)
    {
        sceneNode->setPosition(position);
    }

    void setSize(const Ogre::Vector3& size)
    {
        sceneNode->setScale(Ogre::Vector3::UNIT_SCALE * 0.01f * size);
    }

    void setNearestRoad(Road* road)
    {
        nearestRoad = road;
    }

    Road* getNearestRoad() const
    {
        return nearestRoad;
    }
protected:
    Ogre::Entity* entity;
    Ogre::SceneNode* sceneNode;

    Road* nearestRoad;
};
