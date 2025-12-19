#pragma once

#include "PCH.hpp"

#include "Object.hpp"

class Terrain : public Object
{
public:
    Terrain(const std::string& name, Scene* scene) : Object(name, scene), entity(NULL), sceneNode(NULL)
    {
    }

    virtual ~Terrain()
    {
    }

    virtual void load();

    virtual void unload();
    
    float getHeight(size_t x, size_t z, int offset = 0) const;
protected:
    Ogre::Entity* entity;
    Ogre::SceneNode* sceneNode;
};
