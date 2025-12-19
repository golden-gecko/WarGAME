#include "Dependencies.h"
#include "Graphics.h"
#include "Object.h"

Object::Object(unsigned int id, unsigned int type, const std::string& mesh) : mID(id),
	mType(type), mState(OS_DEFAULT), mMaxWaterDepth(0.0f)
{
	mEntity = Graphics::getSingleton().createEntity(Ogre::StringConverter::toString(id), mesh);
	mEntity->setUserAny(Ogre::Any(this));
	mEntity->setRenderingDistance(512.0f);

	mNode = Graphics::getSingleton().createSceneNode();
	mNode->attachObject(mEntity);
	mNode->setFixedYawAxis(true);

	if (mEntity->getAllAnimationStates())
	{
		mAnimation = mEntity->getAllAnimationStates()->getAnimationStateIterator().getNext();
	}
}

Object::Object(unsigned int id, unsigned int type, const std::string& name, const std::string& mesh) :
	mID(id), mType(type), mName(name), mState(OS_DEFAULT), mMaxWaterDepth(0.0f)
{
	mEntity = Graphics::getSingleton().createEntity(Ogre::StringConverter::toString(id), mesh);
	mEntity->setUserAny(Ogre::Any(this));
	mEntity->setRenderingDistance(512.0f);

	mNode = Graphics::getSingleton().createSceneNode();
	mNode->attachObject(mEntity);
	mNode->setFixedYawAxis(true);

	if (mEntity->getAllAnimationStates())
	{
		mAnimation = mEntity->getAllAnimationStates()->getAnimationStateIterator().getNext();
	}
}

Object::~Object()
{
	Graphics::getSingleton().destroy(mEntity);
	Graphics::getSingleton().destroy(mNode);
}

std::string Object::toString() const
{
	return 
		"Name: " +
		mName +
		"\nDescription: " +
		mDescription +
		"\nHealth: " +
		Ogre::StringConverter::toString(mHealth, 0, 0, 32, std::ios_base::fixed) +
		" / " +
		Ogre::StringConverter::toString(mMaxHealth, 0, 0, 32, std::ios_base::fixed) +
		"\nPosition: " + Ogre::StringConverter::toString(getPosition());
}
