
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Object.h"

#include "Arm.h"
#include "Armour.h"
#include "Body.h"
#include "Engine.h"
#include "Explosive.h"
#include "Player.h"
#include "Reactor.h"
#include "Shield.h"
#include "Teleporter.h"
#include "Weapon.h"

//------------------------------------------------------------------------------

Object::Object()
	:	m_arm(NULL),
		m_armour(NULL),
		m_body(NULL),
		m_engine(NULL),
		m_explosive(NULL),
		m_reactor(NULL),
		m_shield(NULL),
		m_teleporter(NULL),
		m_weapon(NULL),
		m_type(OT_NULL),
		m_state(OS_NORMAL),
		m_player(NULL),
		m_selected(false),
		m_smoke(NULL),
		m_linearVelocity(Ogre::Vector3::ZERO),
		m_linearDamping(Ogre::Vector3::ZERO) { }

//------------------------------------------------------------------------------

void Object::create() {

	m_smoke = EffectManager::getSingletonPtr()->createSmoke();

	m_smoke->setDirection(Ogre::Vector3::UNIT_Y);
}

//------------------------------------------------------------------------------

void Object::destroy() {

	EffectManager::getSingletonPtr()->destroySmoke(m_smoke);
}

//------------------------------------------------------------------------------

Ogre::Vector3 Object::getDirection() {

	return m_body->getDirection();
}

//------------------------------------------------------------------------------

float Object::getEnergyCost() {

	return
		(m_arm ? m_arm->getEnergyCost() : 0.0f) + 
		(m_armour ? m_armour->getEnergyCost() : 0.0f) + 
		(m_body ? m_body->getEnergyCost() : 0.0f) + 
		(m_engine ? m_engine->getEnergyCost() : 0.0f) + 
		(m_explosive ? m_explosive->getEnergyCost() : 0.0f) + 
		(m_reactor ? m_reactor->getEnergyCost() : 0.0f) + 
		(m_shield ? m_shield->getEnergyCost() : 0.0f) + 
		(m_teleporter ? m_teleporter->getEnergyCost() : 0.0f) + 
		(m_weapon ? m_weapon->getEnergyCost() : 0.0f);
}

//------------------------------------------------------------------------------

float Object::getHitPoints() {

	return
		(m_arm ? m_arm->getHitPoints() : 0.0f) + 
		(m_armour ? m_armour->getHitPoints() : 0.0f) + 
		(m_body ? m_body->getHitPoints() : 0.0f) + 
		(m_engine ? m_engine->getHitPoints() : 0.0f) + 
		(m_explosive ? m_explosive->getHitPoints() : 0.0f) + 
		(m_reactor ? m_reactor->getHitPoints() : 0.0f) + 
		(m_shield ? m_shield->getHitPoints() : 0.0f) + 
		(m_teleporter ? m_teleporter->getHitPoints() : 0.0f) + 
		(m_weapon ? m_weapon->getHitPoints() : 0.0f);
}

//------------------------------------------------------------------------------

float Object::getMaxHitPoints() {

	return
		(m_arm ? m_arm->getMaxHitPoints() : 0.0f) + 
		(m_armour ? m_armour->getMaxHitPoints() : 0.0f) + 
		(m_body ? m_body->getMaxHitPoints() : 0.0f) + 
		(m_engine ? m_engine->getMaxHitPoints() : 0.0f) + 
		(m_explosive ? m_explosive->getMaxHitPoints() : 0.0f) + 
		(m_reactor ? m_reactor->getMaxHitPoints() : 0.0f) + 
		(m_shield ? m_shield->getMaxHitPoints() : 0.0f) + 
		(m_teleporter ? m_teleporter->getMaxHitPoints() : 0.0f) + 
		(m_weapon ? m_weapon->getMaxHitPoints() : 0.0f);
}

//------------------------------------------------------------------------------

Ogre::Quaternion Object::getOrientation() {

	return m_body->getOrientation();
}

//------------------------------------------------------------------------------

Ogre::Vector3 Object::getPosition() {

	return m_body->getPosition();
}

//------------------------------------------------------------------------------

bool Object::getSelected() {

	return m_body->getSelected();
}

//------------------------------------------------------------------------------

Ogre::AxisAlignedBox Object::getWorldBoundingBox() {

	return m_body->getWorldBoundingBox();
}

//------------------------------------------------------------------------------

Ogre::Vector3 Object::getWorldCenter() {

	return m_body->getWorldCenter();
}

//------------------------------------------------------------------------------

void Object::setArm(Arm* arm) {

	if (m_arm) {

		m_arm->setParent(NULL);

		m_type &= ~Part::PT_ARM;
	}

	m_arm = arm;

	if (m_arm) {
		
		m_arm->setParent(this);

		m_type |= Part::PT_ARM;

	}
}

//------------------------------------------------------------------------------

void Object::setArmour(Armour* armour) {

	if (m_armour) {

		m_armour->setParent(NULL);

		m_type &= ~Part::PT_ARMOUR;
	}

	m_armour = armour;

	if (m_armour) {
		
		m_armour->setParent(this);

		m_type |= Part::PT_ARMOUR;

	}
}

//------------------------------------------------------------------------------

void Object::setBody(Body* body) {

	if (m_body) {

		m_body->setParent(NULL);

		m_type &= ~Part::PT_BODY;
	}

	m_body = body;

	if (m_body) {
		
		m_body->setParent(this);

		m_type |= Part::PT_BODY;
	}
}

//------------------------------------------------------------------------------

void Object::setEngine(Engine* engine) {

	if (m_engine) {

		m_engine->setParent(NULL);

		m_type &= ~Part::PT_ENGINE;
	}

	m_engine = engine;

	if (m_engine) {
		
		m_engine->setParent(this);

		m_type |= Part::PT_ENGINE;
	}
}

//------------------------------------------------------------------------------

void Object::setExplosive(Explosive* explosive) {

	if (m_explosive) {

		m_explosive->setParent(NULL);

		m_type &= ~Part::PT_EXPLOSIVE;
	}

	m_explosive = explosive;

	if (m_explosive) {

		m_explosive->setParent(this);

		m_type |= Part::PT_EXPLOSIVE;
	}
}

//------------------------------------------------------------------------------

void Object::setOrientation(const Ogre::Quaternion& orientation) {

	m_body->setOrientation(orientation);

	if (m_shield) m_shield->setOrientation(orientation);
	if (m_weapon) m_weapon->setOrientation(orientation);
}

//------------------------------------------------------------------------------

void Object::setPlayer(Player* player) {

	if (m_player && m_reactor) {

		m_player->decreaseMaxEnergyStored(m_reactor->getReactorDesc()->getMaxEnergyStored());
		m_player->decreaseEnergyProduced(m_reactor->getReactorDesc()->getMaxEnergyProduced());
		m_player->decreaseMaxEnergyProduced(m_reactor->getReactorDesc()->getMaxEnergyProduced());
	}

	m_player = player;

	if (m_player && m_reactor) {

		m_player->increaseMaxEnergyStored(m_reactor->getReactorDesc()->getMaxEnergyStored());
		m_player->increaseEnergyProduced(m_reactor->getReactorDesc()->getMaxEnergyProduced());
		m_player->increaseMaxEnergyProduced(m_reactor->getReactorDesc()->getMaxEnergyProduced());
	}
}

//------------------------------------------------------------------------------

void Object::setPosition(const Ogre::Vector3& position) {

	m_body->setPosition(position);

	if (m_arm) m_arm->setPosition(position + Ogre::Vector3(0.0f, m_body->getMaximum().y, 0.0f));
	if (m_shield) m_shield->setPosition(position);
	if (m_weapon) m_weapon->setPosition(position + Ogre::Vector3(0.0f, m_body->getMaximum().y, 0.0f));
}

//------------------------------------------------------------------------------

void Object::setReactor(Reactor* reactor) {

	if (m_reactor) {

		m_reactor->setParent(NULL);

		m_type &= ~Part::PT_REACTOR;
	}

	m_reactor = reactor;

	if (m_reactor) {
		
		m_reactor->setParent(this);

		m_type |= Part::PT_REACTOR;
	}
}

//------------------------------------------------------------------------------

void Object::setSelected(bool selected) {

	m_body->setSelected(selected);
}

//------------------------------------------------------------------------------

void Object::setShield(Shield* shield) {

	if (m_shield) {

		m_shield->setParent(NULL);

		m_type &= ~Part::PT_SHIELD;
	}

	m_shield = shield;

	if (m_shield) {
		
		m_shield->setParent(this);

		m_type |= Part::PT_SHIELD;
	}
}

//------------------------------------------------------------------------------

void Object::setTeleporter(Teleporter* teleporter) {

	if (m_teleporter) {

		m_teleporter->setParent(NULL);

		m_type &= ~Part::PT_TELEPORTER;
	}

	m_teleporter = teleporter;

	if (m_teleporter) {
		
		m_teleporter->setParent(this);

		m_type |= Part::PT_TELEPORTER;
	}
}

//------------------------------------------------------------------------------

void Object::setWeapon(Weapon* weapon) {

	if (m_weapon) {

		m_weapon->setParent(NULL);

		m_type &= ~Part::PT_WEAPON;
	}

	m_weapon = weapon;

	if (m_weapon) {
		
		m_weapon->setParent(this);

		m_type |= Part::PT_WEAPON;
	}
}

//------------------------------------------------------------------------------

void Object::damage(float damage) {

	m_body->damage(damage);
}

//------------------------------------------------------------------------------

void Object::order(const ObjectOrder& order, bool remove) {

	if (remove) {
		
		m_orderList.removeAll();

		if (m_arm) m_arm->setState(Part::PS_NORMAL);
		if (m_engine) m_engine->setState(Part::PS_NORMAL);
		if (m_weapon) m_weapon->setState(Part::PS_NORMAL);

		m_state = OS_NORMAL;
	}

	m_orderList.addBack(order);
}

//------------------------------------------------------------------------------

void Object::rotate(const Ogre::Quaternion& q) {
	
	m_body->rotate(q);

	if (m_arm) m_arm->rotate(q);
	if (m_shield) m_shield->rotate(q);
	if (m_weapon) m_weapon->rotate(q);
}

//------------------------------------------------------------------------------

string Object::toString() {

	static char str[512];

	sprintf(
		str,
		"object\n  name - %s\n  hit points - %.2f/%.2f\n  energy cost - %.2f\n",
		m_name.c_str(),
		getHitPoints(),
		getMaxHitPoints(),
		getEnergyCost());

	string ret = str;

	if (m_armour) {

		static char armour[64];

		sprintf(
			armour,
			"\n  armour - %.2f%%",
			m_armour->getHitPoints() / m_armour->getMaxHitPoints() * 100.0f);

		ret += armour;
	}

	if (m_body) {

		static char body[64];

		sprintf(
			body,
			"\n  body - %.2f%%",
			m_body->getHitPoints() / m_body->getMaxHitPoints() * 100.0f);

		ret += body;
	}

	if (m_engine) {

		static char engine[64];

		sprintf(
			engine,
			"\n  engine - %.2f%%",
			m_engine->getHitPoints() / m_engine->getMaxHitPoints() * 100.0f);

		ret += engine;
	}

	if (m_explosive) {

		static char explosive[64];

		sprintf(
			explosive,
			"\n  explosive - %.2f%%",
			m_explosive->getHitPoints() / m_explosive->getMaxHitPoints() * 100.0f);

		ret += explosive;
	}

	if (m_reactor) {

		static char reactor[64];

		sprintf(
			reactor,
			"\n  reactor - %.2f%%",
			m_reactor->getHitPoints() / m_reactor->getMaxHitPoints() * 100.0f);

		ret += reactor;
	}

	if (m_shield) {

		static char shield[64];

		sprintf(
			shield,
			"\n  shield - %.2f%%",
			m_shield->getHitPoints() / m_shield->getMaxHitPoints() * 100.0f);

		ret += shield;
	}

	if (m_teleporter) {

		static char teleporter[64];

		sprintf(
			teleporter,
			"\n  teleporter - %.2f%%",
			m_teleporter->getHitPoints() / m_teleporter->getMaxHitPoints() * 100.0f);

		ret += teleporter;
	}

	if (m_weapon) {

		static char weapon[64];

		sprintf(
			weapon,
			"\n  weapon - %.2f%%",
			m_weapon->getHitPoints() / m_weapon->getMaxHitPoints() * 100.0f);

		ret += weapon;
	}

	return ret;
}

//------------------------------------------------------------------------------

bool Object::update(float deltaTime) {

	if (getHitPoints() / getMaxHitPoints() < 0.75f) {

		m_smoke->setColour(Ogre::ColourValue(
			0.25f + getHitPoints() / getMaxHitPoints() * 0.5f,
			0.25f + getHitPoints() / getMaxHitPoints() * 0.5f,
			0.25f + getHitPoints() / getMaxHitPoints() * 0.5f,
			0.75f - getHitPoints() / getMaxHitPoints() * 0.5f));
		m_smoke->setEnabled(true);
		m_smoke->setPosition(getWorldCenter());

	} else {

		m_smoke->setEnabled(false);
	}

	//

	switch (m_state) {

		case OS_NORMAL:

			//

			setPosition(getPosition() + m_linearVelocity * deltaTime);

			//

			if (m_orderList.getCount()) {

				switch (m_orderList.getFirst().getType()) {

					case ObjectOrder::OOT_ATTACK_OBJECT:

						if ((m_orderList.getFirst().getParam() != this) && m_weapon) {

							m_weapon->attack((Object*)m_orderList.getFirst().getParam());

							m_state = OS_PROCESSING_ORDER;

						} else {

							m_state = OS_ORDER_FINISHED;
						}

						break;

					case ObjectOrder::OOT_ATTACK_POSITION:

						if (m_weapon) {

							m_weapon->attack(m_orderList.getFirst().getVector());

							m_state = OS_PROCESSING_ORDER;

						} else {

							m_state = OS_ORDER_FINISHED;
						}

						break;

					case ObjectOrder::OOT_CONSTRUCT:

						break;
						
					case ObjectOrder::OOT_FOLLOW:

						if ((m_orderList.getFirst().getParam() != this) && m_engine) {
							
							m_engine->follow((Object*)m_orderList.getFirst().getParam());

							m_state = OS_PROCESSING_ORDER;

						} else {

							m_state = OS_ORDER_FINISHED;
						}

						break;

					case ObjectOrder::OOT_MOVE_TO_OBJECT:

						if ((m_orderList.getFirst().getParam() != this) && m_engine) {
							
							m_engine->move((Object*)m_orderList.getFirst().getParam());

							m_state = OS_PROCESSING_ORDER;

						} else {

							m_state = OS_ORDER_FINISHED;
						}

						break;

					case ObjectOrder::OOT_MOVE_TO_POSITION:

						if (m_engine) {
							
							m_engine->move(m_orderList.getFirst().getVector());

							m_state = OS_PROCESSING_ORDER;

						} else {

							m_state = OS_ORDER_FINISHED;
						}

						break;

					case ObjectOrder::OOT_PATROL:

						break;

					case ObjectOrder::OOT_REPAIR:

						if ((m_orderList.getFirst().getParam() != this) && m_arm) {
							
							m_arm->repair((Object*)m_orderList.getFirst().getParam());

							m_state = OS_PROCESSING_ORDER;

						} else {

							m_state = OS_ORDER_FINISHED;
						}

						break;

					case ObjectOrder::OOT_RESUPPLY:

						if ((m_orderList.getFirst().getParam() != this) && m_arm) {
							
							m_arm->resupply((Object*)m_orderList.getFirst().getParam());

							m_state = OS_PROCESSING_ORDER;

						} else {

							m_state = OS_ORDER_FINISHED;
						}

						break;

					case ObjectOrder::OOT_SELF_DESTRUCT:

						break;

					case ObjectOrder::OOT_STOP:

						break;
				}
			}

			break;

		case OS_PROCESSING_ORDER:

			break;

		case OS_ORDER_FAILED:

			m_orderList.addBack(m_orderList.getFirst());
			m_orderList.removeFront();

			break;

		case OS_BROKEN:

			break;

		case OS_DEAD:

			break;

		case OS_UNDER_CONSTRUCTION:

			break;

		case OS_ORDER_FINISHED:

			m_orderList.removeFront();

			m_state = OS_NORMAL;

			break;
	}

	return true;
}

//------------------------------------------------------------------------------
