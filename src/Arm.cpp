
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Arm.h"

#include "Engine.h"
#include "Weapon.h"

//------------------------------------------------------------------------------

string Arm::toString() {

	return "arm";
}

//------------------------------------------------------------------------------

bool Arm::update(float deltaTime) {

	switch (m_state) {

		case PS_CONSTRUCT:

			break;

		case PS_MODIFY:

			break;

		case PS_REPAIR:

			break;

		case PS_RESUPPLY:

			m_stream->setPosition(getWorldCenter() + getDimensions().z);
			m_stream->setDirection(getDirection());
			m_stream->setColour(Ogre::ColourValue(0.25f, 0.5f, 0.75f));

			if (m_targetObj->getEngine() && m_targetObj->getEngine()->getFuel() < m_targetObj->getEngine()->getMaxFuel()) {

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

				if ((m_targetObj->getPosition() - m_parent->getPosition()).length() < 10.0f) {

					distance = true;
				}

				if (angle && distance) {

					m_targetObj->getEngine()->setFuel(m_targetObj->getEngine()->getFuel() + m_armDesc->getMaxEnergyUsed() * deltaTime);

					m_stream->setEnabled(true);
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
