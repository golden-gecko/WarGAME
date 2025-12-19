#include "Dependencies.h"
#include "Creature.h"
#include "Game.h"
#include "ObjectManager.h"
#include "Terrain.h"
#include "Water.h"

Creature::Creature(unsigned int id, const std::string& mesh) :
	Object(id, OT_CREATURE, mesh),
	mEnergy(25.0f), mMaxEnergy(25.0f),
	mHealthRestore(0.02f), mEnergyRestore(0.1f),
	mExperience(0.0f), mMaxExperience(400.0f),
	mLevel(1), mMaxLevel(8),
	mDamage(10.0f), mSpeed(1.0f), mCurrentAttackDuration(0.0f)
{
}

void Creature::update(float time)
{
	// Restore health.
	if (mHealth < mMaxHealth)
	{
		mHealth += mHealthRestore * time;

		if (mHealth > mMaxHealth)
		{
			mHealth = mMaxHealth;
		}
	}

	// Restore energy.
	if (mEnergy < mMaxEnergy)
	{
		mEnergy += mEnergyRestore * time;

		if (mEnergy > mMaxEnergy)
		{
			mEnergy = mMaxEnergy;
		}
	}

	// Update state.
	switch (mState)
	{
		case OS_DEFAULT:
		{
			setAnimation("cpause1");
			setState(OS_STANDING);

			break;
		}

		case OS_STANDING:
		{
			mAnimation->addTime(time);

			// Start moving in random direction.
			if (Ogre::Math::UnitRandom() > 0.997f)
			{
				// Do not walk into water.
			//	do
				{
					setMoveTarget(Terrain::getSingleton().getRandomPosition(getPosition(), 20.0f));
				}
			//	while (mMoveTarget.y < Water::getSingleton().getLevel() - mMaxWaterDepth);

				setAnimation("cwalk");
				setState(OS_WANDERING);
			}

			break;
		}

		case OS_WANDERING:
		{
			mAnimation->addTime(time);

			if (getPosition().squaredDistance(mMoveTarget) > 0.5f)
			{
				Ogre::Vector3 direction = mMoveTarget - getPosition();

				direction.y = 0.0f;
				direction.normalise();

				setDirection(direction);

				float y = Terrain::getSingleton().getHeight(getPosition() + direction * getSpeed() * time);
				
				if (y > Water::getSingleton().getLevel() - getMaxWaterDepth())
				{
					Game::getSingleton().message(Message(MT_MOVE, mID, direction * getSpeed() * time));
				}
				else
				{
					setAnimation("cpause1");
					setState(OS_STANDING);
				}
			}
			else
			{
				setAnimation("cpause1");
				setState(OS_STANDING);
			}

			break;
		}
	}
}

std::string Creature::toString() const
{
	return
		mName + " (" + mSpecies + ")\n" +
		mDescription + "\n\n" +
		"Health: " + Ogre::StringConverter::toString(mHealth, 0) + " / " +  Ogre::StringConverter::toString(mMaxHealth, 0) + "\n" +
		"Energy: " + Ogre::StringConverter::toString(mEnergy, 0) + " / " +  Ogre::StringConverter::toString(mMaxEnergy, 0);
}
