#pragma once

#include "PCH.hpp"

#include "Object.hpp"

class City : public Object
{
public:
    City(const std::string& name, Scene* scene, const Ogre::Vector3& position, const Ogre::Vector3& size) : Object(name, scene), position(position), size(size)
    {
    }

    virtual void load();

    virtual void unload();

    virtual void update(float time);

	Ogre::Vector3 getPosition() const
	{
		return position;
	}

	Ogre::Vector3 getSize() const
	{
		return size;
	}
protected:
	Ogre::Vector3 position;
    Ogre::Vector3 size;

    std::map<std::string, Object*> objects;
};
