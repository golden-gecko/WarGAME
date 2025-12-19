#pragma once

#include "Dependencies.h"
#include "Terrain.h"
#include "Unit.h"

class Vehicle : public Unit
{
public:
	Vehicle(unsigned int id, const std::string& mesh);

	void setAcceleration(float acceleration) { mAcceleration = acceleration; }
	void setSpeed(float speed) { mSpeed = speed; }
	void setWeaponDamage(float damage) { mWeaponDamage = damage; }
	void setWeaponDamageRadius(float radius) { mWeaponDamageRadius = radius; }
	void setWeaponRange(float range) { mWeaponRange = range; }
	void setWeaponRechargeTime(float recharge) { mWeaponRechargeTime = recharge; }

	void onOrder(const Order& order, bool append = false)
	{
		switch (order.getType())
		{
			case OT_ATTACK_OBJECT:
			case OT_ATTACK_POSITION:
			case OT_DESTROY:
			case OT_FOLLOW:
			case OT_GUARD_OBJECT:
			case OT_GUARD_POSITION:
			case OT_MOVE:
			case OT_STOP:

				Unit::onOrder(order, append);

				break;
		}
	}

	void update(float time);

	std::string toString() const
	{
		return
			Unit::toString();/* + "\n" +
			"Move Speed: " + Ogre::StringConverter::toString(mMoveSpeed / 1000.0f * 3600.0f, 2, 0, 32, std::ios::fixed) + " / " + Ogre::StringConverter::toString(mMaxMoveSpeed / 1000.0f * 3600.0f, 2, 0, 32, std::ios::fixed) + " km/h\n" +
			"Acceleration: " + Ogre::StringConverter::toString(100.0f * 1000.0f / 3600.0f / mAcceleration, 2, 0, 32, std::ios::fixed) + " s\n" +
			"Brake Rate: " + Ogre::StringConverter::toString(100.0f * 1000.0f / 3600.0f / mBrakeRate, 2, 0, 32, std::ios::fixed) + " s\n" +
			"Weapon Damage: " + Ogre::StringConverter::toString(mMaxWeaponDamage, 2, 0, 32, std::ios::fixed) + " HP\n" +
			"Weapon Range: " + Ogre::StringConverter::toString(mMaxWeaponRange, 2, 0, 32, std::ios::fixed) + " m\n" +
			"Weapon Radius: " + Ogre::StringConverter::toString(mMaxWeaponDamageRadius, 2, 0, 32, std::ios::fixed) + " m \n" +
			"Weapon Reload Time: " + Ogre::StringConverter::toString(mWeaponRechargeTime, 2, 0, 32, std::ios::fixed) + " / " + Ogre::StringConverter::toString(mMaxWeaponRechargeTime, 2, 0, 32, std::ios::fixed) + " s";*/
	}
public:
	float mAcceleration;
	float mCurrentWeaponRechargeTime;
	float mSpeed;
	float mWeaponDamage;
	float mWeaponDamageRadius;
	float mWeaponRange;
	float mWeaponRechargeTime;

	unsigned int mAttackDistance;
	unsigned int mAttackType;
	unsigned int mMovementType;
	unsigned int mTargetPriority;
	unsigned int mTargetType;

	Ogre::Vector3	mAttackPosition;
	Ogre::Vector3	mMovePosition;
	unsigned int	mAttackObject;
	unsigned int	mMoveObject;
	Ogre::Vector3	mLastAttackObjectPosition;
	Ogre::Vector3	mLastMoveObjectPosition;
};
