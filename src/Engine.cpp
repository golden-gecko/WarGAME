
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Engine.h"

#include "Body.h"
#include "Core.h"
#include "Object.h"

//------------------------------------------------------------------------------

void Engine::setPartDesc(PartDesc* partDesc) {

	Part::setPartDesc(partDesc);

	m_fuel = m_engineDesc->getMaxFuel();
}

//------------------------------------------------------------------------------

string Engine::toString() {

	static char str[256];

	sprintf(
		str,
		"engine\n  name - %s (installed at %s)\n  hit points - %.2f/%.2f\n  fuel - %.2f/%.2f (%.2f%%)",
		m_name.c_str(),
		m_parent->getName().c_str(),
		m_hitPoints, getMaxHitPoints(),
		m_fuel, m_engineDesc->getMaxFuel(), m_fuel / m_engineDesc->getMaxFuel() * 100.0f);

	return str;
}

//------------------------------------------------------------------------------

bool Engine::update(float deltaTime) {

	switch (m_state) {

		case PS_FOLLOW:

			if (m_fuel && ((m_targetObj->getPosition() - m_parent->getPosition()).length() > 10.0f)) {

				if (m_fuel < 0.0f)

					m_fuel = 0.0f;

				else

					m_fuel -= m_engineDesc->getMaxPower() / 1000.0f * deltaTime;

				if ((m_parent->getOrientation().Inverse() * (m_targetObj->getPosition() - m_parent->getPosition())).x > 0.05f) {

					m_parent->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-35 * deltaTime)), Ogre::Vector3::UNIT_Y));

					m_parent->setPosition(
						Core::getSingletonPtr()->getTerrainHeightVec(
							m_parent->getPosition() +
							m_parent->getDirection() *
							m_engineDesc->getMaxPower() /
							m_parent->getMaxHitPoints() *
							deltaTime / 2));

				} else if ((m_parent->getOrientation().Inverse() * (m_targetObj->getPosition() - m_parent->getPosition())).x < -0.05f) {

					m_parent->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(35 * deltaTime)), Ogre::Vector3::UNIT_Y));

					m_parent->setPosition(
						Core::getSingletonPtr()->getTerrainHeightVec(
							m_parent->getPosition() +
							m_parent->getDirection() *
							m_engineDesc->getMaxPower() /
							m_parent->getMaxHitPoints() *
							deltaTime / 2));

				} else

					m_parent->setPosition(
						Core::getSingletonPtr()->getTerrainHeightVec(
							m_parent->getPosition() +
							m_parent->getDirection() *
							m_engineDesc->getMaxPower() /
							m_parent->getMaxHitPoints() *
							deltaTime));
			}

			break;

		case PS_MOVE_TO_POSITION:

			if (m_fuel && ((m_targetPos - m_parent->getPosition()).length() > 1.0f)) {

				if (m_fuel < 0.0f)
					
					m_fuel = 0.0f;

				else

					m_fuel -= m_engineDesc->getMaxPower() / 1000.0f * deltaTime;

				if ((m_parent->getOrientation().Inverse() * (m_targetPos - m_parent->getPosition())).x > 0.1f) {

					m_parent->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-35 * deltaTime)), Ogre::Vector3::UNIT_Y));

					m_parent->setPosition(
						Core::getSingletonPtr()->getTerrainHeightVec(
							m_parent->getPosition() +
							m_parent->getDirection() *
							m_engineDesc->getMaxPower() /
							m_parent->getMaxHitPoints() *
							deltaTime / 2));

				} else if ((m_parent->getOrientation().Inverse() * (m_targetPos - m_parent->getPosition())).x < -0.1f) {

					m_parent->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(35 * deltaTime)), Ogre::Vector3::UNIT_Y));

					m_parent->setPosition(
						Core::getSingletonPtr()->getTerrainHeightVec(
							m_parent->getPosition() +
							m_parent->getDirection() *
							m_engineDesc->getMaxPower() /
							m_parent->getMaxHitPoints() *
							deltaTime / 2));

				} else {

					m_parent->setPosition(
						Core::getSingletonPtr()->getTerrainHeightVec(
							m_parent->getPosition() +
							m_parent->getDirection() *
							m_engineDesc->getMaxPower() /
							m_parent->getMaxHitPoints() *
							deltaTime));
				}

			} else {

				m_parent->setState(Object::OS_ORDER_FINISHED);

				m_state = PS_NORMAL;
			}

			break;

		case PS_MOVE_TO_OBJECT:

			if (m_fuel && ((m_targetObj->getPosition() - m_parent->getPosition()).length() > 1.0f)) {

				if (m_fuel < 0.0f)
					
					m_fuel = 0.0f;

				else

					m_fuel -= m_engineDesc->getMaxPower() / 1000.0f * deltaTime;

				if ((m_parent->getOrientation().Inverse() * (m_targetObj->getPosition() - m_parent->getPosition())).x > 0.01f) {

					m_parent->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-35 * deltaTime)), Ogre::Vector3::UNIT_Y));

					m_parent->setPosition(
						Core::getSingletonPtr()->getTerrainHeightVec(
							m_parent->getPosition() +
							m_parent->getDirection() *
							m_engineDesc->getMaxPower() /
							m_parent->getMaxHitPoints() *
							deltaTime / 2));

				} else if ((m_parent->getOrientation().Inverse() * (m_targetObj->getPosition() - m_parent->getPosition())).x < -0.01f) {

					m_parent->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(35 * deltaTime)), Ogre::Vector3::UNIT_Y));

					m_parent->setPosition(
						Core::getSingletonPtr()->getTerrainHeightVec(
							m_parent->getPosition() +
							m_parent->getDirection() *
							m_engineDesc->getMaxPower() /
							m_parent->getMaxHitPoints() *
							deltaTime / 2));

				} else

					m_parent->setPosition(
						Core::getSingletonPtr()->getTerrainHeightVec(
							m_parent->getPosition() +
							m_parent->getDirection() *
							m_engineDesc->getMaxPower() /
							m_parent->getMaxHitPoints() *
							deltaTime));

			} else {

				m_parent->setState(Object::OS_ORDER_FINISHED);

				m_state = PS_NORMAL;
			}

			break;
	}

	return Part::update(deltaTime);
}

//------------------------------------------------------------------------------
