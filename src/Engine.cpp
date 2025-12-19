
//------------------------------------------------------------------------------
// Engine.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "Core.h"
#include "Engine.h"
#include "Object.h"
#include "Vehicle.h"

//------------------------------------------------------------------------------

float leftOrRight(Ogre::Vector3 t, float& angle, float speed);

bool Engine::update(float deltaTime){

	if (ps == NULL) {

		ps = Core::getSingletonPtr()->createParticleSystem("smoke_drive");
		m_parent->m_body->m_sceneNode->attachObject(ps);	
		ps->getEmitter(0)->setEnabled(true);

	}

	if (m_target != Vector3(-1.0f)) {

		if (ps->getNumParticles() == 0)

				ps->getEmitter(0)->setEnabled(true);

		Quaternion y;

		float sinYaw = leftOrRight(
			m_target - m_parent->getPosition(),
			m_yaw, 35 * deltaTime);

		y.FromAngleAxis(Radian(Degree(m_yaw)), Vector3::UNIT_Y);

		m_parent->setOrientation(y);

		m_parent->setPosition(
			Core::getSingletonPtr()->getTerrainHeightVec(
			m_parent->getPosition() + Ogre::Vector3(
				 Math::Cos(Radian(Degree(m_yaw))) * 5 * deltaTime,
				 0,
				-Math::Sin(Radian(Degree(m_yaw))) * 5 * deltaTime)));

	} else {

		ps->getEmitter(0)->setEnabled(false);

	}

	return true;

}

//------------------------------------------------------------------------------
