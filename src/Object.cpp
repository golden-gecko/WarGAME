
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

	Ogre::AxisAlignedBox box = m_body->getWorldBoundingBox();
	
	//if (m_weapon)
	
		//box.merge(m_weapon->getWorldBoundingBox());

	return box;
}

//------------------------------------------------------------------------------

Ogre::Vector3 Object::getWorldCenter() {

	return m_body->getWorldCenter();
}

//------------------------------------------------------------------------------

void Object::setArm(Arm* arm) {

	m_arm = arm;

	if (m_arm) m_arm->setParent(this);
}

//------------------------------------------------------------------------------

void Object::setArmour(Armour* armour) {

	m_armour = armour;

	if (m_armour) m_armour->setParent(this);
}

//------------------------------------------------------------------------------

void Object::setBody(Body* body) {

	m_body = body;

	if (m_body) m_body->setParent(this);
}

//------------------------------------------------------------------------------

void Object::setEngine(Engine* engine) {

	m_engine = engine;

	if (m_engine) m_engine->setParent(this);
}

//------------------------------------------------------------------------------

void Object::setExplosive(Explosive* explosive) {

	m_explosive = explosive;

	if (m_explosive) m_explosive->setParent(this);
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

	m_reactor = reactor;

	if (m_reactor) m_reactor->setParent(this);
}

//------------------------------------------------------------------------------

void Object::setSelected(bool selected) {

	m_body->setSelected(selected);
}

//------------------------------------------------------------------------------

void Object::setShield(Shield* shield) {

	m_shield = shield;

	if (m_shield) m_shield->setParent(this);
}

//------------------------------------------------------------------------------

void Object::setTeleporter(Teleporter* teleporter) {

	m_teleporter = m_teleporter;

	if (m_teleporter) m_teleporter->setParent(this);
}

//------------------------------------------------------------------------------

void Object::setWeapon(Weapon* weapon) {

	m_weapon = weapon;

	if (m_weapon) m_weapon->setParent(this);
}

//------------------------------------------------------------------------------

void Object::damage(float damage) {

	m_body->damage(damage);
}

//------------------------------------------------------------------------------

void Object::order(const ObjectOrder& order, bool remove) {

	if (remove) {
		
		m_orderList.removeAll();

		if (m_arm) m_engine->setState(Part::PS_NORMAL);
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

	switch (m_state) {

		case OS_NORMAL:

			setPosition(getPosition() + m_linearVelocity * deltaTime);

			if (m_orderList.getCount()) {

				switch (m_orderList.getFirst().getType()) {

					case ObjectOrder::OOT_ATTACK_OBJECT:

						if (m_weapon) {

							m_weapon->attack((Object*)m_orderList.getFirst().getParam());

							m_state = OS_PROCESSING_ORDER;

						} else {

							m_state = OS_ORDER_FINISHED;
						}

						break;

					case ObjectOrder::OOT_ATTACK_POSITION:

						break;

					case ObjectOrder::OOT_CONSTRUCT:

						break;
						
					case ObjectOrder::OOT_FOLLOW:

						if (m_engine) {
							
							m_engine->follow((Object*)m_orderList.getFirst().getParam());

							m_state = OS_PROCESSING_ORDER;

						} else {

							m_state = OS_ORDER_FINISHED;
						}

						break;

					case ObjectOrder::OOT_MOVE_TO_OBJECT:

						if (m_engine) {
							
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

						if (m_arm) {
							
							m_arm->repair((Object*)m_orderList.getFirst().getParam());

							m_state = OS_PROCESSING_ORDER;

						} else {

							m_state = OS_ORDER_FINISHED;
						}

						break;

					case ObjectOrder::OOT_RESUPPLY:

						if (m_arm) {
							
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
