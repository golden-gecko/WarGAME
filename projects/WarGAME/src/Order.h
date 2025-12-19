#pragma once

#include "Dependencies.h"

enum OrderType
{
	/// Do not use. For GUI and Input use only.
	OT_ATTACK,

	/// Do not use. For GUI and Input use only.
	OT_GUARD,

	/// Do not use. For GUI and Input use only.
	OT_LOOK,

	/// Do not use. For GUI and Input use only.
	OT_NONE,


	/// Object attacks other object.
	OT_ATTACK_OBJECT,

	/// Object attacks position.
	OT_ATTACK_POSITION,

	/// Object builds a structure.
	OT_BUILD,

	/// Object captures an object (changes player).
	OT_CAPTURE,

	/// Object contructs an object.
	OT_CONSTRUCT,

	/// Object explodes ;)
	OT_DESTROY,

	/// Object disables.
	OT_DISABLE,

	/// Object powers up.
	OT_ENABLE,

	/// Objects follows other object.
	OT_FOLLOW,

	/// Object guards other object.
	OT_GUARD_OBJECT,

	/// Object guards position.
	OT_GUARD_POSITION,

	/// Object rotates toward object.
	OT_LOOK_AT_OBJECT,

	/// Object rotates toward position.
	OT_LOOK_AT_POSITION,

	/// Object moves to given coordinates.
	OT_MOVE,

	/// Object cancels any orders and goes to default state.
	OT_STOP,

	/// Object moves to given coordinates, pushes order to end of list and executes next order.
	OT_PATROL,

	/// Object repairs other object (stops if object has full health).
	OT_REPAIR
};

class Order
{

public:

	Order(unsigned int type) : mType(type)
	{
	}

	Order(unsigned int type, unsigned int i) : mType(type), mInt(i)
	{
	}

	Order(unsigned int type, const std::string& s) : mType(type), mString(s)
	{
	}

	Order(unsigned int type, const Ogre::Vector3& v) : mType(type), mVector(v)
	{
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

	void setBool(bool b)
	{
		mBool = b;
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

	void operator = (bool b)
	{
		mBool = b;
	}

	void operator = (float f)
	{
		mFloat = f;
	}

	void operator = (unsigned int i)
	{
		mInt = i;
	}

	void operator = (const std::string& s)
	{
		mString = s;
	}

	void operator = (const Ogre::Vector3& v)
	{
		mVector = v;
	}

protected:

	unsigned int	mType;

	bool			mBool;
	float			mFloat;
	unsigned int	mInt;
	std::string		mString;
	Ogre::Vector3	mVector;

};
