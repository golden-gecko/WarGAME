
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Weapon.h"

#include "Object.h"
#include "ObjectDescManager.h"
#include "ObjectManager.h"

//------------------------------------------------------------------------------

void Weapon::setPartDesc(PartDesc* partDesc) {

	PartWithMesh::setPartDesc(partDesc);

	m_reloadTime = m_weaponDesc->getMaxReloadTime();
	m_ammunition = m_weaponDesc->getMaxAmmunition();
}

//------------------------------------------------------------------------------

void Weapon::fire() {

	if ((m_reloadTime >= m_weaponDesc->getMaxReloadTime()) && (m_ammunition)) {

		m_reloadTime = 0.0f;

		m_ammunition--;

		Object* o = ObjectManager::getSingletonPtr()->create("missile", ObjectDescManager::getSingletonPtr()->getByName("missile"));

		if (o) {

			o->setPosition(getWorldCenter() + getDimensions().x / 2.0f);
			o->setOrientation(getOrientation());
			o->setLinearVelocity(getDirection() * m_weaponDesc->getMaxPower() / o->getMaxHitPoints() + Ogre::Vector3(0.0f, -0.1f, 0.0f));
		}
	}
}

//------------------------------------------------------------------------------

string Weapon::toString() {

	static char str[256];

	sprintf(
		str,
		"weapon\n  name - %s (installed at %s)\n  hit points - %.2f/%.2f\n  ammunition - %i/%i",
		m_name.c_str(),
		m_parent->getName().c_str(),
		m_hitPoints, getMaxHitPoints(),
		m_ammunition, getMaxAmmunition());

	return str;
}

//------------------------------------------------------------------------------

bool Weapon::update(float deltaTime) {

	// Reload

	if (m_reloadTime < m_weaponDesc->getMaxReloadTime())

		m_reloadTime += deltaTime;

	else if (m_reloadTime > m_weaponDesc->getMaxReloadTime())

		m_reloadTime = m_weaponDesc->getMaxReloadTime();

	// State

	switch (m_state) {

		case PS_NORMAL:

			break;

		case PS_PROCESSING_ORDER:
			
			// Attak position.

			if (m_targetPos != Ogre::Vector3(-1.0f)) {

				if ((getOrientation().Inverse() * (m_targetPos - getWorldCenter())).x > 0.01f)

					rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-25 * deltaTime)), Ogre::Vector3::UNIT_Y));

				else if ((getOrientation().Inverse() * (m_targetPos - m_parent->getPosition())).x < -0.01f)

					rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(25 * deltaTime)), Ogre::Vector3::UNIT_Y));

				else

					fire();

			} else {

				// Attack object,
				
				if (m_targetObj) {

					// if it is still alive - fire,

					if (m_targetObj->getHitPoints() > 0.0f) {

						Ogre::Vector3 v = (getOrientation().Inverse() * (m_targetObj->getWorldCenter() - getWorldCenter()));

						if (v.x > 0.02f)

							rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-25.0f * deltaTime)), Ogre::Vector3::UNIT_Y));

						else if (v.x < -0.02f)

							rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(25.0f * deltaTime)), Ogre::Vector3::UNIT_Y));

						else

							fire();					

					// if not - stop.

					} else {

						m_targetObj = NULL;

						m_parent->setState(Object::OS_ORDER_FINISHED);

						m_state = PS_NORMAL;
					}
				}
			}

			break;

	}

	return Part::update(deltaTime);
}

//------------------------------------------------------------------------------
