#pragma once

#include "Dependencies.h"

enum MessageType
{
	MT_CREATE_OBJECT,
	MT_MOVE,
	MT_SHOOT_POSITION,
	MT_SHOOT_OBJECT,
	MT_DESTROY_OBJECT,
	MT_CHANGE_RESOURCE,
	MT_INCREASE_HEALTH,
	MT_ATTACK
};

class Message
{

public:

	Message(unsigned int type, unsigned int sender) : mType(type), mSender(sender)
	{
	}

	Message(unsigned int type, unsigned int sender, float f) : mType(type), mSender(sender), mFloat(f)
	{
	}

	Message(unsigned int type, unsigned int sender, unsigned int i) : mType(type), mSender(sender), mInt(i)
	{
	}

	Message(unsigned int type, unsigned int sender, const std::string& s) : mType(type), mSender(sender), mString(s)
	{
	}

	Message(unsigned int type, unsigned int sender, const Ogre::Vector3& v) : mType(type), mSender(sender), mVector(v)
	{
	}

	Message(unsigned int type, unsigned int sender, unsigned int i, float f) : mType(type), mSender(sender), mInt(i), mFloat(f)
	{
	}

	unsigned int getSender() const
	{
		return mSender;
	}

	unsigned int getType() const
	{
		return mType;
	}

	float getFloat() const
	{
		return mFloat;
	}

	unsigned int getInt() const
	{
		return mInt;
	}

	const std::string& getString() const
	{
		return mString;
	}

	const Ogre::Vector3& getVector() const
	{
		return mVector;
	}

	void setFloat(float f)
	{
		mFloat = f;
	}

	void setInt(unsigned int i)
	{
		mInt = i;
	}

	void setString(const std::string& s)
	{
		mString = s;
	}

	void setVector(const Ogre::Vector3& v)
	{
		mVector = v;
	}

	void operator << (float f)
	{
		mFloat = f;
	}

	void operator << (unsigned int i)
	{
		mInt = i;
	}

	void operator << (const std::string& s)
	{
		mString = s;
	}

	void operator << (const Ogre::Vector3& v)
	{
		mVector = v;
	}

protected:

	const unsigned int	mType;
	const unsigned int	mSender;

	float				mFloat;
	unsigned int		mInt;
	std::string			mString;
	Ogre::Vector3		mVector;

};