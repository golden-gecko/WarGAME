
//------------------------------------------------------------------------------
// BattleFieldCamera.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "BattleFieldCamera.h"
#include "Core.h"
#include "ObjectTemp.h"

//------------------------------------------------------------------------------

void BattleFieldCamera::init() {

	m_ogreCamera = Core::getSingletonPtr()->getCamera();
}

//------------------------------------------------------------------------------

void BattleFieldCamera::update(float deltaTime) {

	switch (m_state) {

		case CS_FOLLOW_OBJECT:

			m_ogreCamera->setPosition(
				m_target->getPosition() - Vector3(
											m_target->getDirection().x * 10.0f,
											-5.0f,
											m_target->getDirection().z * 10.0f));

			m_ogreCamera->lookAt(m_target->getPosition() + Vector3(0, 4, 0));

			break;

		case CS_TRACK_OBJECT:

			m_ogreCamera->lookAt(m_target->getPosition());

			break;

	}
}

//------------------------------------------------------------------------------
