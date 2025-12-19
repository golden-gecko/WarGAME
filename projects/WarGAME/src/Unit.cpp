#include "Dependencies.h"
#include "Game.h"
#include "Unit.h"

Unit::Unit(unsigned int id, unsigned int type, const std::string&
	mesh) : Object(id, type, mesh), mHideFactor(0.0f), mPlayer(NULL),
	mRepeatOrders(false)
{
}

void Unit::update(float time)
{
	switch (mState)
	{
		case OS_RECEIVE_ORDER:
		{
			switch (mOrders.front().getType())
			{
				case OT_DESTROY:
				{
					Game::getSingleton().message(Message(MT_DESTROY_OBJECT, mID, mID));

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
			mState = OS_DEFAULT;

			break;
		}
	}
}
