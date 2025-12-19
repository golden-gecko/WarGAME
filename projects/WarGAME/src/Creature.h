#pragma once

#include "Dependencies.h"
#include "Object.h"

enum CreatureSpecies
{
	CS_SPIDER,
	CS_DEER,
	CS_BEETLE,
	CS_BAT,
	CS_BADGER,
	CS_BOAR,
	CS_BUGBEAR,
	CS_JAGUAR,
	CS_DIRE_CAT,
	CS_DIRE_BOAR
};

class Creature : public Object
{
public:
	Creature(unsigned int id, const std::string& mesh);

	void update(float time);
	std::string toString() const;

	bool isFriendly(const std::string& species) const
	{
		return (mSpecies == species) ? true : false;
	}

	const std::string& getSpecies() const
	{
		return mSpecies;
	}
	float getSightDistance() const
	{
		return mSightDistance;
	}
	float getSpeed() const
	{
		return mSpeed;
	}

	void setSpeed(float speed)
	{
		mSpeed = speed;
	}
	void setSightDistance(float distance)
	{
		mSightDistance = distance;
	}
	void setDamage(float damage)
	{
		mDamage = damage;
	}
	void setEnergy(float energy)
	{
		mEnergy = energy;
	}
	void setMaxEnergy(float energy)
	{
		mMaxEnergy = energy;
	}
	void setExperience(float experience)
	{
		mExperience = experience;
	}
	void setMaxLevel(unsigned int level)
	{
		mMaxLevel = level;
	}
	void setMaxExperience(float experience)
	{
		mMaxExperience = experience;
	}
	void setSpecies(const std::string& species)
	{
		mSpecies = species;
	}
	void setHealthRestore(float health)
	{
		mHealthRestore = health;
	}
	void setEnergyRestore(float energy)
	{
		mEnergyRestore = energy;
	}
	void setAttackDuration(float duration)
	{
		mAttackDuration = duration;
	}
	void setMoveTarget(const Ogre::Vector3& target)
	{
		mMoveTarget = target;
	}
protected:
	std::string		mSpecies;
	float			mEnergy;
	float			mMaxEnergy;
	float			mHealthRestore;
	float			mEnergyRestore;
	float			mExperience;
	float			mMaxExperience;
	unsigned int	mLevel;
	unsigned int	mMaxLevel;
	float 			mSightDistance;
	float 			mDamage;
	float 			mSpeed;
	float 			mCurrentAttackDuration;
	float 			mAttackDuration;
	Ogre::Vector3	mMoveTarget;
	unsigned int	mAttackTarget;
};
