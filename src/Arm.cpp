
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Arm.h"

#include "Body.h"
#include "Engine.h"
#include "Explosive.h"
#include "Object.h"
#include "Weapon.h"

//------------------------------------------------------------------------------

string Arm::toString() {

	return "arm";
}

//------------------------------------------------------------------------------

bool Arm::update(float deltaTime) {

	switch (m_state) {

		case PS_NORMAL:

			m_stream->setEnabled(false);

			break;

		case PS_CONSTRUCT:

			break;

		case PS_MODIFY:

			break;

		case PS_REPAIR:

			m_stream->setColour(Ogre::ColourValue(0.25f, 0.75f, 0.25f));
			m_stream->setDirection(getDirection());
			m_stream->setPosition(getWorldCenter() + getDirection() * getDimensions().z / 2.0f);

			if (m_targetObj->getHitPoints() < m_targetObj->getMaxHitPoints()) {

				bool angle = false;

				if ((getOrientation().Inverse() * (m_targetObj->getPosition() - getWorldCenter())).x > 0.01f) {

					rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-25 * deltaTime)), Ogre::Vector3::UNIT_Y));

					m_stream->setEnabled(false);

				} else if ((getOrientation().Inverse() * (m_targetObj->getPosition() - m_parent->getPosition())).x < -0.01f) {

					rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(25 * deltaTime)), Ogre::Vector3::UNIT_Y));

					m_stream->setEnabled(false);

				} else {

					angle = true;
				}

				bool distance = false;

				if ((m_targetObj->getPosition() - m_parent->getPosition()).length() < 12.0f) {

					distance = true;
				}

				if (angle && distance) {

					if (m_targetObj->getBody()->getHitPoints() < m_targetObj->getBody()->getMaxHitPoints())

						m_targetObj->getBody()->setHitPoints(m_targetObj->getBody()->getHitPoints() + m_armDesc->getMaxEnergyUsed() * deltaTime);
					
					m_stream->setEnabled(true);
				}

			} else {

				m_stream->setEnabled(false);

				m_parent->setState(Object::OS_ORDER_FINISHED);

				m_state = PS_NORMAL;
			}

			break;

		case PS_RESUPPLY:

			m_stream->setDirection(getDirection());
			m_stream->setPosition(getWorldCenter() + getDirection() * getDimensions().z / 2.0f);

			if ((m_targetObj->getEngine() && m_targetObj->getEngine()->getFuel() < m_targetObj->getEngine()->getMaxFuel()) ||(m_targetObj->getWeapon() && m_targetObj->getWeapon()->getAmmunition() < m_targetObj->getWeapon()->getMaxAmmunition()) ) {

				bool angle = false;

				if ((getOrientation().Inverse() * (m_targetObj->getPosition() - getWorldCenter())).x > 0.01f) {

					rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-25 * deltaTime)), Ogre::Vector3::UNIT_Y));

					m_stream->setEnabled(false);

				} else if ((getOrientation().Inverse() * (m_targetObj->getPosition() - m_parent->getPosition())).x < -0.01f) {

					rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(25 * deltaTime)), Ogre::Vector3::UNIT_Y));

					m_stream->setEnabled(false);

				} else {

					angle = true;
				}

				bool distance = false;

				if ((m_targetObj->getPosition() - m_parent->getPosition()).length() < 12.0f) {

					distance = true;
				}

				if (angle && distance) {

					if (m_targetObj->getEngine() && m_targetObj->getEngine()->getFuel() < m_targetObj->getEngine()->getMaxFuel()) {
						
						m_targetObj->getEngine()->setFuel(m_targetObj->getEngine()->getFuel() + m_armDesc->getMaxEnergyUsed() * deltaTime);

						m_stream->setColour(Ogre::ColourValue(0.25f, 0.5f, 0.75f));
						m_stream->setEnabled(true);

					} else if (m_targetObj->getWeapon() && m_targetObj->getWeapon()->getAmmunition() < m_targetObj->getWeapon()->getMaxAmmunition()) {

						m_targetObj->getWeapon()->setAmmunition(m_targetObj->getWeapon()->getAmmunition() + m_armDesc->getMaxEnergyUsed() * deltaTime);

						m_stream->setColour(Ogre::ColourValue(0.75f, 0.0f, 0.0f));
						m_stream->setEnabled(true);
					}
				}

			} else {

				m_stream->setEnabled(false);

				m_parent->setState(Object::OS_ORDER_FINISHED);

				m_state = PS_NORMAL;
			}

			break;
	}

	return Part::update(deltaTime);
}

//------------------------------------------------------------------------------
