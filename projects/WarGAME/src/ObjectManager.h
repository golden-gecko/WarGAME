#pragma once

#include "Dependencies.h"
#include "Creature.h"
#include "Debug.h"
#include "Plant.h"
#include "Resource.h"
#include "Structure.h"
#include "Vehicle.h"

typedef std::map<unsigned int, Object*> ObjectMap;
typedef std::vector<Object*>			ObjectVector;

/// Manages objects.
class ObjectManager : public Ogre::Singleton<ObjectManager>
{
public:
	ObjectManager();

	Object* create(const std::string& name,
		const Ogre::Vector3& position = Ogre::Vector3::ZERO);

	const ObjectMap& get() const
	{
		return mObjects;
	}

	Object* get(unsigned int id) const
	{
		ASSERT(id > 0);

		ObjectMap::const_iterator i = mObjects.find(id);

		if (i != mObjects.end())
		{
			return i->second;
		}

		return NULL;
	}

	/// Search for all objects within given radius.
	const ObjectVector& get(const Ogre::Vector3& position, float radius)
	{
		mResults.clear();

		for (ObjectMap::const_iterator i = mObjects.begin(); i != mObjects.end(); ++i)
		{
			if (i->second->getPosition().distance(position) <= radius)
			{
				mResults.push_back(i->second);
			}
		}

		return mResults;
	}

	/// Search for all enemy objects within given radius.
	const ObjectVector& get(const Ogre::Vector3& position, float radius, Player* player)
	{
		ASSERT(position.length() > 0.0f);
		ASSERT(radius > 0.0f);
		ASSERT(player);

		mResults.clear();

		for (ObjectMap::const_iterator i = mObjects.begin(); i != mObjects.end(); ++i)
		{
			if (i->second->getPosition().distance(position) <= radius)
			{
				if (Unit* unit = dynamic_cast<Unit*>(i->second))
				{
					if (unit->isEnemy(player))
					{
						mResults.push_back(i->second);
					}
				}
			}
		}

		return mResults;
	}

	/// Search for all enemy objects within given radius.
	/*
	const std::vector<Object*>& get(const Ogre::Vector3& position, float radius, Player* player)
	{
		mResults.clear();

		for (ObjectMap::const_iterator i = mObjects.begin(); i != mObjects.end(); ++i)
		{
			if ((i->second->getPosition().distance(position) <= radius) && (i->second->isEnemy(player)))
			{
				mResults.push_back(i->second);
			}
		}

		return mResults;
	}
	*/

	/*
	const std::vector<Object*>& get(Player* player, bool ally = true)
	{
		ASSERT(player);

		mResults.clear();

		for (ObjectMap::const_iterator i = mObjects.begin(); i != mObjects.end(); ++i)
		{
			if (ally)
			{
				if (i->second->isUnit() && i->second->isUnit()->getPlayer() == player)
				{
					mResults.push_back(i->second);
				}
			}
			else
			{
				if (i->second->isUnit() && i->second->isUnit()->getPlayer() != player)
				{
					mResults.push_back(i->second);
				}
			}
		}

		return mResults;
	}
	*/

	const std::vector<Object*>& get(const Ogre::Vector3& position, float radius, const std::string& species)
	{
		mResults.clear();

		for (ObjectMap::const_iterator i = mObjects.begin(); i != mObjects.end(); ++i)
		{
			if (Creature* creature = dynamic_cast<Creature*>(i->second))
			{
				if (creature->getPosition().distance(position) <= radius)
				{
					if (creature->isFriendly(species) == false)
					{
						mResults.push_back(i->second);
					}
				}
			}
		}

		return mResults;
	}

	void destroy(unsigned int id)
	{
		ASSERT(id > 0);

		ObjectMap::iterator i = mObjects.find(id);

		if (i != mObjects.end())
		{
			delete i->second;

			mObjects.erase(i);
		}
	}

	void destroyAll()
	{
		for (ObjectMap::const_iterator i = mObjects.begin(); i != mObjects.end(); ++i)
		{
			delete i->second;
		}

		mObjects.clear();
	}

	void update(float time)
	{
		for (ObjectMap::const_iterator i = mObjects.begin(); i != mObjects.end(); ++i)
		{
			i->second->update(time);
		}
	}

	unsigned int getNextID()
	{
		mLastID++;

		return mLastID;
	}
protected:
	unsigned int	mLastID;
	ObjectVector	mResults;

	std::map<unsigned int, Object*>			mObjects;
	std::multimap<unsigned int, Object*>	mTypes;
};
