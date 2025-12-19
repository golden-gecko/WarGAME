#pragma once

#include "PCH.hpp"

class Object;

#include "Scene.hpp"

class Object
{
public:
    Object(const std::string& name, Scene* scene) : name(name), scene(scene)
    {
    }

    virtual ~Object()
    {
        unload();
    }

    const std::string& getName() const
    {
        return name;
    }

    virtual void load()
    {
        unload();
    }

    virtual void unload()
    {
    }

    virtual void update(float time)
    {
    }
protected:
    std::string name;
    Scene* scene;
};
