#pragma once

#include "PCH.hpp"

#include "Object.hpp"

namespace Debug
{
	class Axis : public Object
	{
	public:
		Axis(const std::string& name, Scene* scene) : Object(name, scene), manualObject(NULL), sceneNode(NULL)
		{
		}

		virtual void load();

		virtual void unload();
	protected:
		Ogre::ManualObject* manualObject;
		Ogre::SceneNode* sceneNode;
	};
}
