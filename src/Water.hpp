#pragma once

#include "PCH.hpp"

#include "Object.hpp"
#include "Terrain.hpp"

class Water : public Object
{
public:
    Water(const std::string& name, Scene* scene, Terrain* terrain) : Object(name, scene), terrain(terrain), entity(NULL), sceneNode(NULL)
    {
    }

    virtual ~Water()
    {
    }

    virtual void load();

    virtual void unload();

    virtual void update(float time);

    float getHeight(size_t x, size_t z) const;
protected:
    Terrain* terrain;

    Ogre::Entity* entity;
    Ogre::SceneNode* sceneNode;

    float* water;
};
