#pragma once

#include "PCH.hpp"

#include "Object.hpp"

class Road : public Object
{
public:
    enum Type
    {
        X,
        Z
    };

    Road(const std::string& name, Scene* scene) : Object(name, scene), entity(NULL), sceneNode(NULL)
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
        // We have to switch Y with Z, because of planes normal vector.
        sceneNode->setScale(Ogre::Vector3::UNIT_SCALE * 0.005f * Ogre::Vector3(size.x, size.z, size.y));
    }

    void setType(Type type)
    {
        switch (type)
        {
            case X:
                entity->setMaterialName("RoadX");
                break;

            case Z:
                entity->setMaterialName("RoadZ");
                break;
        }
    }
protected:
    Ogre::Entity* entity;
    Ogre::SceneNode* sceneNode;
};
