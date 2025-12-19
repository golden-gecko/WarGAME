#pragma once

#include "Dependencies.h"
#include "Graphics.h"

enum PlayerType
{
	PT_GOD,
	PT_HUMAN,
	PT_COMPUTER,
	PT_SPECTATOR
};

struct ResourceDetails
{
	float maximal;
	float current;
	float produced;
	float use;

	ResourceDetails() : maximal(0.0f), current(0.0f), produced(0.0f), use(0.0f)
	{
	}
};

typedef std::map<std::string, ResourceDetails> ResourceMap;

class Player
{
public:
	Player(unsigned int type, const std::string& name, const Ogre::ColourValue& colour);

	const std::string& getName() const
	{
		return mName;
	}

	unsigned int getType() const
	{
		return mType;
	}

	void setName(const std::string& name)
	{
		mName = name;
	}

	const Ogre::ColourValue& getColour() const
	{
		return mColour;
	}

	void update(float time);

	std::string toString() const
	{
		std::stringstream s;

		s.fill('0');
		s.width(8);

		s << std::hex << std::uppercase << mColour.getAsRGBA();

		return
			"Name: " + mName +
			"\nColour: #" + s.str() +
			"\nSelected: " + Ogre::StringConverter::toString(mSelected.size());
	}
protected:
	unsigned int			mType;
	std::string				mName;
	Ogre::ColourValue		mColour;
	Ogre::TexturePtr		mSight;
//------------------------------------------------------------------------------
// Groups
//------------------------------------------------------------------------------
public:
	typedef std::set<unsigned int>					ObjectContainer;
	typedef std::set<unsigned int>::iterator		ObjectContainerIterator;
	typedef std::set<unsigned int>::const_iterator	ObjectContainerConstIterator;

	const ObjectContainer& getGroup(unsigned int number) const
	{
		ASSERT(number < 10);

		return mGroups[number];
	}
	const ObjectContainer& getSelected() const
	{
		return mSelected;
	}

	void orderSelected(const Order& order, bool append = false);
	void removeFromGroups(unsigned int id);
	void removeFromSelection(unsigned int id);
	void selectAll(bool select = true);
	void selectGroup(unsigned int number, bool create = false);
	void selectObject(Object* object, bool append = false);
protected:
	ObjectContainer mSelected;
	ObjectContainer mGroups[10];
//------------------------------------------------------------------------------
// Resources
//------------------------------------------------------------------------------
public:
	ResourceDetails& getResource(const std::string& name)
	{
		return mResources[name];
	}

	const ResourceMap& getResources() const
	{
		return mResources;
	}

protected:
	ResourceMap mResources;
};
