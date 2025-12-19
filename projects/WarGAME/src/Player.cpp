#include "Dependencies.h"
#include "ObjectManager.h"
#include "Player.h"

Player::Player(unsigned int type, const std::string& name,
	const Ogre::ColourValue& colour) : mType(type), mName(name), mColour(colour)
{
}

void Player::update(float time)
{
	for (ResourceMap::iterator i = mResources.begin(); i != mResources.end(); ++i)
	{
		i->second.current += (i->second.produced - i->second.use) * time;

		if (i->second.current > i->second.maximal)
		{
			i->second.current = i->second.maximal;
		}
		else if (i->second.current < 0.0f)
		{
			i->second.current = 0.0f;
		}
	}
}

void Player::orderSelected(const Order& order, bool append)
{
	for (ObjectContainerConstIterator i = mSelected.begin(); i != mSelected.end(); ++i)
	{
		if (Object* object = ObjectManager::getSingleton().get(*i))
		{
			if (Unit* unit = dynamic_cast<Unit*>(object))
			{
				unit->onOrder(order, append);
			}
		}
	}
}

void Player::selectObject(Object* object, bool append)
{
	ASSERT(object);

	if (append == false)
	{
		// Clear current selection.
		for (ObjectContainerConstIterator i = mSelected.begin(); i != mSelected.end(); ++i)
		{
			if (Object* object = ObjectManager::getSingleton().get(*i))
			{
				object->setSelected(false);
			}
		}
		mSelected.clear();

		// Select object.
		object->setSelected(true);
		mSelected.insert(object->getID());
	}
	else if (object->getSelected())
	{
		object->setSelected(false);
		mSelected.erase(mSelected.find(object->getID()));
	}
	else
	{
		object->setSelected(true);
		mSelected.insert(object->getID());
	}
}

void Player::selectGroup(unsigned int number, bool create)
{
	ASSERT(number < 10);

	if (create)
	{
		mGroups[number] = mSelected;
	}
	else
	{
		for (ObjectContainerConstIterator i = mSelected.begin(); i != mSelected.end(); ++i)
		{
			if (Object* object = ObjectManager::getSingleton().get(*i))
			{
				object->setSelected(false);
			}
		}

		mSelected = mGroups[number];

		for (ObjectContainerConstIterator i = mSelected.begin(); i != mSelected.end(); ++i)
		{
			if (Object* object = ObjectManager::getSingleton().get(*i))
			{
				object->setSelected(true);
			}
		}
	}
}

void Player::selectAll(bool select)
{
	if (select)
	{
		const ObjectMap& objects = ObjectManager::getSingleton().get();

		for (ObjectMap::const_iterator i = objects.begin(); i != objects.end(); ++i)
		{
			if (i->second->getSelected() == false)
			{
				i->second->setSelected(select);
				mSelected.insert(i->first);
			}
		}
	}
	else
	{
		for (ObjectContainerConstIterator i = mSelected.begin(); i != mSelected.end(); ++i)
		{
			if (Object* object = ObjectManager::getSingleton().get(*i))
			{
				object->setSelected(false);
			}
		}
		mSelected.clear();
	}
}

void Player::removeFromGroups(unsigned int id)
{
	for (unsigned int n = 0; n < 10; ++n)
	{
		ObjectContainerIterator i = mGroups[n].find(id);

		if (i != mGroups[n].end())
		{
			mGroups[n].erase(i);
		}
	}
}

void Player::removeFromSelection(unsigned int id)
{
	ObjectContainerIterator i = mSelected.find(id);

	if (i != mSelected.end())
	{
		mSelected.erase(i);
	}
}
