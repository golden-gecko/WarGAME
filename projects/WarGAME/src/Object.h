#pragma once

#include "Dependencies.h"
#include "Order.h"
#include "Terrain.h"

class Player;

enum ObjectType
{
	OT_CREATURE			=  1 <<  0,
	OT_PLANT			=  1 <<  1,
	OT_RESOURCE			=  1 <<  2,

	OT_UNIT				=  1 <<  3,
	OT_STRUCTURE		=  1 <<  4,
	OT_VEHICLE			=  1 <<  5,

	OT_FACTORY			= (1 <<  6) | OT_UNIT | OT_STRUCTURE,
	OT_MINE				= (1 <<  7) | OT_UNIT | OT_STRUCTURE,
	OT_RADAR			= (1 <<  8) | OT_UNIT | OT_STRUCTURE,
	OT_LABORATORY		= (1 <<  9) | OT_UNIT | OT_STRUCTURE,
	OT_FORTIFICATION	= (1 << 10) | OT_UNIT | OT_STRUCTURE,
	OT_TURRET			= (1 << 11) | OT_UNIT | OT_STRUCTURE
};

enum ObjectState
{
	/// Default state. Used to reset object.
	OS_DEFAULT,

	/// Creature is just standing.
	OS_STANDING,
	/// Creature is moving randomly.
	OS_WANDERING,
	/// Creature is attacking.
	OS_ATTACKING,
	/// Creature is chasing victim.
	OS_CHASING,
	/// Creature is retreating from attacker.
	OS_RETREATING,

	/// Unit is receiving order.
	OS_RECEIVE_ORDER,
	/// Units has completed order and removing it from quene.
	OS_REMOVE_ORDER,

	/// Factory is begining contruction.
	OS_BEGINING_CONSTRUCTION,
	/// Factory is constructing vehicle.
	OS_CONSTRUCTING,
	/// Factory is repairing vehicle.
	OS_REPAIRING,
	/// Factory is ending contruction and waiting for vehicle to leave.
	OS_ENDING_CONSTRUCTION,

	OS_ATTACKING_OBJECT,
	OS_ATTACKING_POSITION,
	OS_CAPTURING,
	OS_FOLLOWING,
	OS_GUARDING_OBJECT,
	OS_GUARDING_POSITION,
	OS_MOVING_TO_POSITION,
	OS_UNDER_CONSTRUCTION
};

enum OptionType
{
	OT_ATTACK_DISTANCE	= 1,
	OT_ATTACK_TYPE		= 2,
	OT_MOVEMENT_TYPE	= 3,
	OT_RETREAT_DAMAGE	= 4,
	OT_TARGET_CLASS		= 5,
	OT_TARGET_PRIORITY	= 6
};

/// Closer to enemy means better accuracy.
enum AttackDistance
{
	/// Attack from maximal distance.
	AD_MAXIMAL = 1,
	/// Keep at least 75% of maximal distance.
	AD_MEDIUM = 2,
	/// Keep at least 50% of maximal distance.
	AD_SHORT = 3
};

enum AttackType
{
	/// Shoot to every enemy in range.
	AT_FIRE_AT_WILL = 1,
	/// Shoot only if attacked.
	AT_RETURN_FIRE = 2,
	/// Do not shoot.
	AT_HOLD_FIRE = 3
};

enum MovementType
{
	/// Chase enemy until killed.
	MT_CHASE_LONG = 1,
	/// Chase enemy for short time and then return to previous position.
	MT_CHASE_SHORT = 2,
	/// Do not move.
	MT_HOLD_POSITION = 3
};

enum RetreatDamage
{
	/// Fight to death.
	RD_NEVER = 1,
	/// Reatreat when health goes below 75%.
	RD_P_75 = 2,
	/// Reatreat when health goes below 50%.
	RD_P_50 = 3,
	/// Reatreat when health goes below 25%.
	RD_P_25 = 4
};

enum TargetClass
{
	/// Attack everything.
	TC_ALL = 1,
	/// Attack only prefered type of enemy units (if there are some in range).
	TC_CUSTOM = 2
};

enum TargetPriority
{
	/// Attack closest enemy unit.
	TP_CLOSEST = 1,
	/// Attack strongest enemy unit.
	TP_STRONGEST = 2,
	/// Attack weakest enemy unit.
	TP_WEAKEST = 3
};

class Object
{
public:
	Object(unsigned int id, unsigned int type, const std::string& mesh);
	Object(unsigned int id, unsigned int type, const std::string& name, const std::string& mesh);

	virtual ~Object();

	const std::string& getDescription() const { return mDescription; }
	const std::string& getName() const { return mName; }

	Ogre::Vector3 getCenter() const { return mEntity->getWorldBoundingBox().getCenter(); }
	Ogre::Vector3 getDirection() const { return mNode->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z; }
	Ogre::Vector3 getSize() const { return mEntity->getWorldBoundingBox().getSize(); }

	const Ogre::Vector3& getPosition() const { return mNode->getPosition(); }
	const Ogre::Vector3& getScale() const { return mNode->getScale(); }

	float getHealth() const { return mHealth; }
	float getMaxHealth() const { return mMaxHealth; }
	float getMaxWaterDepth() const { return mMaxWaterDepth; }
	float getRadius() const { return mEntity->getBoundingRadius(); }

	unsigned int getID() const { return mID; }
	unsigned int getType() const { return mType; }

	bool getSelected() const { return mNode->getShowBoundingBox(); }
	bool getType(unsigned int type) const { return (mType & type) == type; }

	void setAnimation(const std::string& name)
	{
		mAnimation->setEnabled(false);
		mAnimation = mEntity->getAnimationState(name);
		mAnimation->setEnabled(true);
		mAnimation->setLoop(true);
	}
	void setPosition(float x, float y, float z) { mNode->setPosition(x, y, z); }
	void setPosition(const Ogre::Vector3& position) { mNode->setPosition(position); }
	void setScale(float scale) { mNode->setScale(scale, scale, scale); }
	void setScale(float x, float y, float z) { mNode->setScale(x, y, z); }
	void setScale(const Ogre::Vector3& scale) { mNode->setScale(scale); }
	void setName(const std::string& name) { mName = name; }
	void setHealth(float health) { mHealth = health; }
	void setMaxHealth(float health) { mMaxHealth = health; }
	void setState(unsigned int state) { mState = state; }
	void setDescription(const std::string& description) { mDescription = description; }
	void setSelected(bool selected) { mNode->showBoundingBox(selected); }
	void setDirection(const Ogre::Vector3& direction) { mNode->setDirection(direction, Ogre::Node::TS_WORLD); }
	void setMaxSlope(float slope) { mMaxSlope = slope; }
	void setMaxWaterDepth(float depth) { mMaxWaterDepth = depth; }

	virtual bool onHeal(unsigned int source, float health)
	{
		mHealth += health;

		if (mHealth < mMaxHealth)
		{
			return false;
		}

		mHealth = mMaxHealth;

		return true;
	}
	virtual bool onHit(unsigned int source, float damage, const Ogre::Vector3& diretion)
	{
		mHealth -= damage;

		if (mHealth > 0.0f)
		{
			return false;
		}

		mHealth = 0.0f;

		return true;
	}
	virtual void onMove(const Ogre::Vector3& velocity)
	{
		mNode->setPosition(Terrain::getSingleton().getPosition(mNode->getPosition() + velocity));
	}
	virtual void onBeginContruction(unsigned int object) { }
	virtual void onCollision(unsigned int object) { }
	virtual void onCreate(unsigned int creator = 0) { }
	virtual void onDestroy(unsigned int destroyer = 0) { }
	virtual void onShoot(unsigned int target, float damage, bool hit, bool killed) { }

	virtual void update(float time) { }
	virtual std::string toString() const;
protected:
	unsigned int			mID;
	unsigned int			mType;
	unsigned int			mState;

	std::string				mDescription;
	std::string				mMesh;
	std::string				mName;

	float					mHealth;
	float					mMaxHealth;
	float					mMaxSlope;
	float					mMaxWaterDepth;

	Ogre::AnimationState*	mAnimation;
	Ogre::Entity*			mEntity;
	Ogre::SceneNode*		mNode;
};
