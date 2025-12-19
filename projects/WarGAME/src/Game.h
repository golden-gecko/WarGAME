#pragma once

#include "Dependencies.h"
#include "Effect.h"
#include "Message.h"
#include "Player.h"
#include "TemplateManager.h"

typedef std::multimap<unsigned int, Message> MessageMap;

class Game : public Ogre::Singleton<Game>
{
public:
	Game();

	bool init();
	void shutdown();

	unsigned int getGameSpeed() const
	{
		return mGameSpeed;
	}

	void setGameSpeed(unsigned int speed)
	{
		if (speed > 9)
		{
			mGameSpeed = 9;
		}
		else if (speed < 0)
		{
			mGameSpeed = 0;
		}
		else
		{
			mGameSpeed = speed;
		}
	}

	void increaseGameSpeed()
	{
		if (mGameSpeed < 9)
		{
			mGameSpeed++;
		}
	}

	void decreaseGameSpeed()
	{
		if (mGameSpeed > 0)
		{
			mGameSpeed--;
		}
	}

	void pause()
	{
		mGameSpeed = mGameSpeed ? 0 : 1;
	}
protected:
	unsigned int mGameSpeed;
public:
	/*
	void order(Order& order, bool force = false)
	{
		const std::set<unsigned int>& selected = getActivePlayer()->getSelected();

		// Units should move in formation.
		if (order.getType() == OT_MOVE)
		{
			enum FormationType
			{
				FT_NONE,
				FT_CIRCLE,
				FT_RECTANGLE,
				FT_TRIANGLE
			};

			FormationType type = FT_RECTANGLE;

			switch (type)
			{
				case FT_NONE:
				{
					Object* first = NULL;
					Ogre::Vector3 pos = order.getVector();
					Ogre::Vector3 center;
					unsigned int counter = 0;

					for (std::set<unsigned int>::const_iterator i = selected.begin(); i != selected.end(); ++i)
					{
						if (getObject((unsigned int)*i))
						{
							if (counter)
							{
								center += getObject((unsigned int)*i)->getPosition();
							}
							else
							{
								center = getObject((unsigned int)*i)->getPosition();
							}

							counter++;
						}
					}

					center /= counter;

					for (std::set<unsigned int>::const_iterator i = selected.begin(); i != selected.end(); ++i)
					{
						if (getObject((unsigned int)*i))
						{
							order.setVector(pos + getObject((unsigned int)*i)->getPosition() - center);

							if (getObject((unsigned int)*i))
							{
								getObject((unsigned int)*i)->order(order, force);
							}
						}
					}

					break;
				}

				case FT_RECTANGLE:
				{
					unsigned int size = (unsigned int)sqrt((float)selected.size()) * 10;
					std::set<unsigned int>::const_iterator object = selected.begin();
					Ogre::Vector3 position = order.getVector();

					unsigned int z, x;

					for (z = 0; z <= size; z += 10)
					{
						for (x = 0; x <= size; x += 10)
						{
							if ((object != selected.end()))
							{
								order.setVector(position + Ogre::Vector3((float)x, 0.0f, (float)z));

								if (getObject(*object))
								{
									getObject(*object)->order(order, force);
								}

								++object;
							}
						}
					}

					break;
				}
			}
		}
		else
		{
			for (std::set<unsigned int>::const_iterator i = selected.begin(); i != selected.end(); ++i)
			{
				if (getObject((unsigned int)*i))
				{
					getObject((unsigned int)*i)->order(order, force);
				}
			}
		}
	}

	void selectAll(bool select)
	{
	//	if (select)
		{
			std::set<unsigned int>& selected = getActivePlayer()->getSelected();

			for (std::set<unsigned int>::const_iterator i = selected.begin(); i != selected.end(); i++)
			{
				if (getObject((unsigned int)*i))
				{
					getObject((unsigned int)*i)->setSelected(false);
				}
			}

			selected.clear();
		}
	}

	void select(Object* o, bool mode = false)
	{
		std::set<unsigned int>& selected = getActivePlayer()->getSelected();

		if (o)
		{
			if (mode)
			{
				if (o->getSelected())
				{
					selected.erase(selected.find(o->getID()));

					o->setSelected(false);
				}
				else
				{
					selected.insert(o->getID());

					o->setSelected(true);
				}
			}
			else
			{
				for (std::set<unsigned int>::const_iterator i = selected.begin(); i != selected.end(); i++)
				{
					if (getObject((unsigned int)*i))
					{
						getObject((unsigned int)*i)->setSelected(false);
					}
				}

				selected.clear();
				selected.insert(o->getID());

				o->setSelected(true);
			}
		}
	}
	*/

	void update(float time);

	Player* getActivePlayer() const
	{
		return mActivePlayer;
	}

	void setActivePlayer(Player* player);

	std::string toString() const
	{
		return
			"Requests: " + Ogre::StringConverter::toString(mPathQuene.size()) +
			"\nBest: " + Ogre::StringConverter::toString(Graphics::getSingleton().getRenderWindow()->getBestFPS()) +
			"\nAvarage: " + Ogre::StringConverter::toString(Graphics::getSingleton().getRenderWindow()->getAverageFPS()) +
			"\nWorst: " + Ogre::StringConverter::toString(Graphics::getSingleton().getRenderWindow()->getWorstFPS()) +
			"\nSpeed: " + Ogre::StringConverter::toString(mGameSpeed);
	}

	/*
	void selectGroup(unsigned int n)
	{
		const std::set<unsigned int>& selected = mActivePlayer->getSelected();

		for (std::set<unsigned int>::const_iterator itr = selected.begin(); itr != selected.end(); ++itr)
		{
			if (getObject(*itr))
			{
				getObject(*itr)->setSelected(false);
			}
		}

		mActivePlayer->mSelected.clear();

		//

		const std::set<unsigned int>& group = mActivePlayer->getGroup(n);

		for (std::set<unsigned int>::const_iterator itr = group.begin(); itr != group.end(); ++itr)
		{
			if (getObject(*itr))
			{
				getObject(*itr)->setSelected(true);
			}
		}

		mActivePlayer->mSelected = group;
	}
	*/

protected:
	unsigned int			mActiveObject;
	Player*					mActivePlayer;

//------------------------------------------------------------------------------
// Messages
//------------------------------------------------------------------------------

public:

	void message(const Message& m)
	{
		mMessages.insert(std::make_pair(m.getType(), m));
	}

protected:

	std::multimap<unsigned int, Message> mMessages;

//------------------------------------------------------------------------------
// Path Finding
//------------------------------------------------------------------------------

public:

	void find(unsigned int object, const Ogre::Vector3& target)
	{
		for (std::vector<PathQueneItem>::iterator itr = mPathQuene.begin(); itr != mPathQuene.end(); ++itr)
		{
			if (itr->mObject == object)
			{
				mPathQuene.erase(itr);

				break;
			}
		}

		mPathQuene.push_back(PathQueneItem(object, target));
	}

protected:

	struct PathQueneItem
	{
		unsigned int	mObject;
		Ogre::Vector3	mTarget;

		PathQueneItem(unsigned int object, const Ogre::Vector3& target) : mObject(object), mTarget(target)
		{
		}
	};

	std::vector<PathQueneItem> mPathQuene;



	typedef std::multimap<std::string, Effect*> EffectMap;

	std::multimap<std::string, Effect*> mEffects;

	void createEffect(const std::string& name, const Ogre::Vector3& position, const Ogre::Vector3& direction = Ogre::Vector3::NEGATIVE_UNIT_Z)
	{
		for (EffectMap::const_iterator i = mEffects.begin(); i != mEffects.end(); ++i)
		{
			if (i->first == name && i->second->getEnabled() == false)
			{
				i->second->setEnabled(true);
				i->second->setPosition(position);
				i->second->setDirection(direction);

				break;
			}
		}
	}
//------------------------------------------------------------------------------
// Save / Load
//------------------------------------------------------------------------------
public:
	bool save(const std::string& name);
	bool load(const std::string& name);
};
