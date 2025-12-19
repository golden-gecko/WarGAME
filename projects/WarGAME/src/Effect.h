#pragma once

#include "Dependencies.h"

class Effect
{
public:
	Effect(const std::string& name, const std::string& script);

	bool getEnabled() const
	{
		for (unsigned short i = 0; i < mParticleSystem->getNumEmitters(); ++i)
		{
			if (mParticleSystem->getEmitter(i)->getEnabled())
			{
				return true;
			}
		}

		return false;
	}

	void setDirection(const Ogre::Vector3& direction)
	{
		mSceneNode->setDirection(direction, Ogre::Node::TS_WORLD);
	}

	void setEnabled(bool enabled)
	{
		for (unsigned short i = 0; i < mParticleSystem->getNumEmitters(); ++i)
		{
			mParticleSystem->getEmitter(i)->setEnabled(enabled);
		}
	}

	void setPosition(const Ogre::Vector3& position)
	{
		mSceneNode->setPosition(position);
	}
protected:
	Ogre::ParticleSystem*	mParticleSystem;
	Ogre::SceneNode*		mSceneNode;
};
