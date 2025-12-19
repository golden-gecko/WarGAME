#pragma once

#include "Dependencies.h"

class Water : public Ogre::Singleton<Water>
{
public:
	void init(Ogre::SceneManager* scene, float level = 24.0f);
	void load(const std::string& material);
	void unload();

	float getLevel() const
	{
		return mLevel;
	}

	void setLevel(float level)
	{
		mNode->setPosition(
			mNode->getPosition().x,
			mLevel = level,
			mNode->getPosition().z);
	}
protected:
	float				mLevel;
	Ogre::SceneManager*	mScene;
	Ogre::Material*		mMaterial;
	Ogre::Mesh*			mMesh;
	Ogre::Entity*		mEntity;
	Ogre::SceneNode*	mNode;
};
