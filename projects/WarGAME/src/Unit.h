#pragma once

#include "Dependencies.h"
#include "Object.h"
#include "Order.h"
#include "Player.h"

class Unit : public Object
{
public:
	void update(float time);

	Player* getPlayer() const { return mPlayer; }

	bool isAlly(Player* player) const { return mPlayer == player; }
	bool isEnemy(Player* player) const { return mPlayer != player; }

	float getSightDistance() const { return mSightDistance; }
	const std::map<std::string, float>& getCost() const { return mCost; }

	virtual void setCost(const std::map<std::string, float>& cost) { mCost = cost; }
	virtual void setPlayer(Player* player) { mPlayer = player; }
	virtual void setRepeatOrders(bool repeat) { mRepeatOrders = repeat; }
	virtual void setSightDistance(float distance) { mSightDistance = distance; }

	float getCost(const std::string& name) const
	{
		std::map<std::string, float>::const_iterator i = mCost.find(name);

		if (i != mCost.end())
		{
			return i->second;
		}

		return 0.0f;
	}

	void onOrder(const Order& order, bool append = false)
	{
		if (append == false)
		{
			mOrders.clear();
		}

		mOrders.push_back(order);

		if (mOrders.size() == 1)
		{
			mState = OS_RECEIVE_ORDER;
		}
	}

	std::string toString() const
	{
		return
			Object::toString() +
			"\nPlayer: " + mPlayer->getName() +
			"\nSight Distance: " + Ogre::StringConverter::toString(mSightDistance, 2, 0, 32, std::ios::fixed) +
			"\nOrder Count: " + Ogre::StringConverter::toString(mOrders.size());
	}
protected:
	Unit(unsigned int id, unsigned int type, const std::string& mesh);

	std::map<std::string, float>	mCost;
	float							mHideFactor;
	std::list<Order>				mOrders;
	Player*							mPlayer;
	bool							mRepeatOrders;
	float							mSightDistance;
};
