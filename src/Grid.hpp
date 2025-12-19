#pragma once

#include "PCH.hpp"

#include "Object.hpp"
#include "Terrain.hpp"

namespace Debug
{
	class Grid : public Object
	{
	public:
		Grid(const std::string& name, Scene* scene, Terrain* terrain) : Object(name, scene), terrain(terrain), manualObject(NULL), entity(NULL), sceneNode(NULL)
		{
		}

		virtual void load();

		virtual void unload();
	protected:
        Terrain* terrain;

		Ogre::ManualObject* manualObject;
		Ogre::Entity* entity;
        Ogre::SceneNode* sceneNode;
	};
}
