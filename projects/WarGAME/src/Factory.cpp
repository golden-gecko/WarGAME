#include "Dependencies.h"
#include "Factory.h"
#include "Game.h"
#include "ObjectManager.h"

Factory::Factory(unsigned int id, const std::string& mesh) : Structure(id,
	OT_FACTORY, mesh), mStartPoint(3.0f, 0.0f, 3.0f), mRallyPoint(10.0f, 0.0f, 10.0f)
{
}

void Factory::onOrder(const Order& order, bool append)
{
	switch (order.getType())
	{
		case OT_CONSTRUCT:
		case OT_REPAIR:
		case OT_STOP:

			Structure::onOrder(order, append);

			break;
	}
}

void Factory::update(float time)
{
	Structure::update(time);

	switch (mState)
	{
		case OS_DEFAULT:
		{
			break;
		}

		case OS_RECEIVE_ORDER:
		{
			switch (mOrders.front().getType())
			{
				case OT_CONSTRUCT:
				{
					mTemplateName = mOrders.front().getString();
					mState = OS_BEGINING_CONSTRUCTION;

					break;
				}

				case OT_STOP:
				{
					mOrders.clear();
					mState = OS_DEFAULT;

					break;
				}
			}

			break;
		}

		case OS_REMOVE_ORDER:
		{
			mOrders.pop_front();

			if (mOrders.size())
			{
				mState = OS_RECEIVE_ORDER;
			}
			else
			{
				mState = OS_DEFAULT;
			}

			break;
		}

		case OS_BEGINING_CONSTRUCTION:
		{
			Game::getSingleton().message(Message(MT_CREATE_OBJECT, mID, mOrders.front().getString()));

			break;
		}

		case OS_CONSTRUCTING:
		{
			if (ObjectManager::getSingleton().get(mCurrentContructed))
			{
				Game::getSingleton().message(Message(MT_INCREASE_HEALTH, mID, mCurrentContructed, 1.0f * time));
			}
			else
			{
				Order order(OT_MOVE); order.setVector(getPosition() + mRallyPoint);
				Object* object = ObjectManager::getSingleton().get(mCurrentContructed);
				(dynamic_cast<Unit*>(object))->onOrder(order);

				mState = OS_REMOVE_ORDER;
			}

			break;
		}

		case OS_REPAIRING:
		{
			break;
		}

		case OS_ENDING_CONSTRUCTION:
		{
			mState = OS_REMOVE_ORDER;

			break;
		}
	}
}

std::string Factory::toString()
{
	return Structure::toString() + "\n" +
		"Constructed: " + Ogre::StringConverter::toString(mUnitsConstructed);
}

void Factory::onBeginContruction(unsigned int object)
{
	mCurrentContructed = object;
	mState = OS_CONSTRUCTING;

	Ogre::Vector3 pos = Terrain::getSingleton().getPosition(getPosition() + mStartPoint);
	Object* o = ObjectManager::getSingleton().get(object);
	o->setPosition(pos);
	(dynamic_cast<Unit*>(o))->setPlayer(mPlayer);
}
