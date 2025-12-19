
//------------------------------------------------------------------------------
// Weapon.cpp
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Core.h"
#include "Missile.h"
#include "ObjectManagerTemp.h"
#include "PartDescManagerT.h"
#include "Weapon.h"

//------------------------------------------------------------------------------

Weapon::Weapon(ObjectTemp* parent)

	:	Body(parent),
		m_yaw(0.0f),
		m_pitch(0.0f),
		m_reloadTime(0.0f),
		m_ammunition(0),
		m_target(NULL),
		m_flag(WF_FIRE_AT_WILL)

{
	m_name = "Weapon #" + Core::getSingletonPtr()->getDataCounterStr();
	m_type = PT_WEAPON;
}

//------------------------------------------------------------------------------

bool Weapon::fire() {

	if ((m_reloadTime >= m_partDesc->isWeaponDesc()->m_maxReloadTime) && m_ammunition) {

		m_reloadTime = 0.0f;

		m_ammunition--;

		static BodyDesc* bodyDesc = PartDescManagerTemp::getSingletonPtr()->getByName("missile")->isBodyDesc();

		Missile* missile = new Missile(m_parent);

		missile->m_body->setDesc(bodyDesc);
		missile->setPosition(getWorldCenter());
		missile->setPlayer(m_parent->m_player);
		missile->setOrientation(getOrientation());

		ObjectManagerTemp::getSingletonPtr()->add(missile);

		return true;
	}

	return false;
}

//------------------------------------------------------------------------------

void Weapon::setDesc(PartDesc* partDesc) {

	Core::getSingletonPtr()->destroyEntity(m_entity);

	if (partDesc && partDesc->isWeaponDesc()) {

		Part::setDesc(partDesc);

		m_entity = Core::getSingletonPtr()->createEntity(m_partDesc->isWeaponDesc()->m_meshName);
		m_entity->setCastShadows(m_partDesc->isWeaponDesc()->m_castShadows);
		m_entity->setUserAny(Any(this));

		m_sceneNode->attachObject(m_entity);

		m_reloadTime = m_partDesc->isWeaponDesc()->m_maxReloadTime;
		m_ammunition = m_partDesc->isWeaponDesc()->m_maxAmmunition;

	} else {

		Part::setDesc(NULL);

		m_entity = NULL;
		m_reloadTime = 0.0f;
		m_ammunition = 0;
	}
}

//------------------------------------------------------------------------------

string Weapon::toString() {

	static char str[512];

	sprintf(str,
		"\
		Weapon\n\
		%s\n\
		  Reload Time %.2f\n\
		  Ammunition %i\n",
		Part::toString().c_str(),
		m_reloadTime,
		m_ammunition);

	if (m_partDesc)

		return str + m_partDesc->toString();

	return string(str) + "No Weapon Desc";
}

//------------------------------------------------------------------------------

bool Weapon::update(float deltaTime) {

	if (m_reloadTime < m_partDesc->isWeaponDesc()->m_maxReloadTime)

		m_reloadTime += deltaTime;

	else if (m_reloadTime > m_partDesc->isWeaponDesc()->m_maxReloadTime)

		m_reloadTime = m_partDesc->isWeaponDesc()->m_maxReloadTime;

	if (m_target) {

		if (m_target->m_state != ObjectTemp::OS_DEAD) {

			float sinYaw = m_parent->leftOrRight(
				m_target->getWorldCenter() - m_sceneNode->getPosition(),
				m_yaw,
				m_partDesc->isWeaponDesc()->m_maxTurnSpeed * deltaTime);

			float sinPitch = m_parent->upOrDown(
				m_target->getWorldCenter() - m_sceneNode->getPosition(),
				m_pitch,
				m_partDesc->isWeaponDesc()->m_maxTurnSpeed * deltaTime);

			Quaternion y, z;

			y.FromAngleAxis(Ogre::Radian(Ogre::Degree(m_yaw)), Vector3::UNIT_Y);
			z.FromAngleAxis(Ogre::Radian(Ogre::Degree(m_pitch)), Vector3::UNIT_Z);

			m_sceneNode->setOrientation(y * z);

			RaySceneQueryResult result = Core::getSingletonPtr()->whatWouldHit(
				getWorldCenter(), getDirection());

			for (RaySceneQueryResult::iterator itr = result.begin(); itr != result.end(); itr++) {

				if (itr->worldFragment)

					break;

				if (itr->movable && itr->movable->getUserAny().isEmpty() == false) {

					ObjectTemp* object = Core::getSingletonPtr()->ogreAnyToObject(itr->movable->getUserAny());

					if (object) {

						if (object == m_parent || object->m_state == ObjectTemp::OS_DEAD || object->m_type == ObjectTemp::OT_MISSILE)

							continue;

						if (object->isEnemy(m_parent))

							fire();

						break;

					} // if (object)

				} // if (itr->movable && itr->movable->getUserAny().isEmpty() == false)

			} // for (RaySceneQueryResult::iterator itr = result.begin(); itr != result.end(); itr++)

		} else {

			m_target = NULL;
		}

	} else {

		m_timeSinceLastAiCheck += deltaTime;

		if (m_timeSinceLastAiCheck >= m_timeToNextAiCheck) {

			m_timeSinceLastAiCheck = 0.0f;
			m_timeToNextAiCheck = rand() % 1000 / 1000.0f;

			//*
			if (m_target = ObjectManagerTemp::getSingletonPtr()->getNearestEnemy(m_parent))

				if (m_target->m_state == ObjectTemp::OS_DEAD)

					m_target = NULL;
			//*/

		}
	}

	return true;
}

//------------------------------------------------------------------------------
