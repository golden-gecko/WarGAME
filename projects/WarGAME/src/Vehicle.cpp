#include "Dependencies.h"
#include "Game.h"
#include "ObjectManager.h"
#include "Vehicle.h"

Vehicle::Vehicle(unsigned int id, const std::string& mesh) : Unit(id,
	OT_VEHICLE, mesh), mCurrentWeaponRechargeTime(0.0f)
{
}

void Vehicle::update(float time)
{
	Unit::update(time);

	// Reload weapon.
	if (mCurrentWeaponRechargeTime < mWeaponRechargeTime)
	{
		mCurrentWeaponRechargeTime += time;

		if (mCurrentWeaponRechargeTime > mWeaponRechargeTime)
		{
			mCurrentWeaponRechargeTime = mWeaponRechargeTime;
		}
	}

	// Execute orders.
	if (mOrders.size())
	{
		const Order& order = mOrders.front();

		switch (order.getType())
		{
			case OT_MOVE:
			{
				// My position.
				Ogre::Vector3 ths = getPosition();
				ths.y = 0.0f;

				// Destination point.
				Ogre::Vector3 obj = order.getVector();
				obj.y = 0.0f;

				// Are we close to destination point?
				if (ths.distance(obj) > 3.0f)
				{
					// Rotate toward target.
					Ogre::Vector3 dir = obj - ths;
					dir.normalise();
					setDirection(dir);

					// Try to move.
					mSpeed += mAcceleration * time;
					Game::getSingleton().message(Message(MT_MOVE, mID, dir * mSpeed * time));
				}
				// We have reached the destination point.
				else
				{
					mSpeed = 0.0f;
					mState = OS_REMOVE_ORDER;
				}

				break;
			}

			case OT_FOLLOW:
			{
				if (Object* object = ObjectManager::getSingleton().get(order.getInt()))
				{
					if (object == this)
					{
						mState = OS_REMOVE_ORDER;
					}

					// My position.
					Ogre::Vector3 ths = getPosition();
					ths.y = 0.0f;

					// Target position.
					Ogre::Vector3 obj = object->getPosition();
					obj.y = 0.0f;

					// Are we close to target?
					if (ths.distance(obj) > getRadius() + object->getRadius())
					{
						// Rotate toward target.
						Ogre::Vector3 dir = obj - ths;
						dir.normalise();
						setDirection(dir);

						// Try to move.
						mSpeed += mAcceleration * time;
						Game::getSingleton().message(Message(MT_MOVE, mID, dir * mSpeed * time));
					}
					// We are close to target. Stop.
					else
					{
						mSpeed = 0.0f;
					}
				}
				// Target was destroyed. Cancel this order.
				else
				{
					mSpeed = 0.0f;
					mState = OS_REMOVE_ORDER;
				}

				break;
			}

			case OT_ATTACK_OBJECT:
			{
				if (Object* object = ObjectManager::getSingleton().get(order.getInt()))
				{
					if (object == this)
					{
						mState = OS_REMOVE_ORDER;
					}

					// My position.
					Ogre::Vector3 ths = getPosition();
					ths.y = 0.0f;

					// Target position.
					Ogre::Vector3 obj = object->getPosition();
					obj.y = 0.0f;

					// Rotate toward target.
					Ogre::Vector3 dir = obj - ths;
					dir.normalise();
					setDirection(dir);

					// Are we close to target?
					if (ths.distance(obj) > mWeaponRange)
					{
						// Try to move.
						mSpeed += mAcceleration * time;
						Game::getSingleton().message(Message(MT_MOVE, mID, dir * mSpeed * time));
					}
					// We are close to target. Stop.
					else
					{
						mSpeed = 0.0f;

						Game::getSingleton().message(Message(OT_ATTACK_OBJECT, getID(), order.getInt()));
					}
				}
				// Target was destroyed. Cancel this order.
				else
				{
					mSpeed = 0.0f;
					mState = OS_REMOVE_ORDER;
				}

				break;
			}

			case OT_ATTACK_POSITION:
			{
				// My position.
				Ogre::Vector3 ths = getPosition();
				ths.y = 0.0f;

				// Destination point.
				Ogre::Vector3 obj = order.getVector();
				obj.y = 0.0f;

				// Rotate toward target.
				Ogre::Vector3 dir = obj - ths;
				dir.normalise();
				setDirection(dir);

				// Are we close to destination point?
				if (ths.distance(obj) > mWeaponRange)
				{
					// Try to move.
					mSpeed += mAcceleration * time;
					Game::getSingleton().message(Message(MT_MOVE, mID, dir * mSpeed * time));
				}
				// We have reached the destination point.
				else
				{
					mSpeed = 0.0f;

					Message m(OT_ATTACK_POSITION, mID);
					
					m << mWeaponDamage;
					m << obj;

					Game::getSingleton().message(m);
				}

				break;
			}

			case OT_LOOK_AT_OBJECT:
			{
				if (Object* object = ObjectManager::getSingleton().get(order.getInt()))
				{
					if (object == this)
					{
						mState = OS_REMOVE_ORDER;
					}

					Ogre::Vector3 me = getPosition();
					Ogre::Vector3 target = object->getPosition();

					me.y = 0.0f;
					target.y = 0.0f;

					if (me.distance(target) <= getSightDistance())
					{
						Ogre::Vector3 dir = target - me;
						dir.y = 0.0f;
						dir.normalise();

						setDirection(dir);
					}
				}
				else
				{
					mState = OS_REMOVE_ORDER;
				}

				break;
			}

			case OT_LOOK_AT_POSITION:
			{
				Ogre::Vector3 me = getPosition();
				Ogre::Vector3 target = order.getVector();

				Ogre::Vector3 dir = me - target;
				dir.y = 0.0f;
				dir.normalise();

				setDirection(dir);

				mState = OS_REMOVE_ORDER;

				break;
			}
		}
	}
	else
	{
	}

	switch (mState)
	{
		case OS_DEFAULT:
		{
			mSpeed = 0.0f;
		}
	}
}
