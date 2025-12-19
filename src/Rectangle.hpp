#pragma once

#include "PCH.hpp"

#include "Object.hpp"

namespace Debug
{
	class Rectangle : public Object
	{
	public:
		Rectangle(const std::string& name, Scene* scene, const Ogre::Vector3& position, const Ogre::Vector3& size) : Object(name, scene), entity(NULL), sceneNode(NULL), position(position), size(size)
		{
		}

		virtual void load();

		virtual void unload();
	protected:
		Ogre::Entity* entity;
		Ogre::SceneNode* sceneNode;

		Ogre::Vector3 position;
		Ogre::Vector3 size;
	};
}
