
//------------------------------------------------------------------------------
// Engine.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Core.h"
#include "Engine.h"
#include "ObjectTemp.h"
#include "Vehicle.h"

//------------------------------------------------------------------------------

Engine::Engine(ObjectTemp* parent) : Part(parent), m_yaw(0.0f), m_target(Vector3(-1.0f)) {

	m_name = "Engine #" + Core::getSingletonPtr()->getDataCounterStr();
	m_type = PT_ENGINE;
}

//------------------------------------------------------------------------------

void Engine::setDesc(PartDesc* partDesc) {

	if (partDesc && partDesc->isEngineDesc())

		Part::setDesc(partDesc);

	else

		Part::setDesc(NULL);

}

//------------------------------------------------------------------------------

string Engine::toString() {

	if (m_partDesc)

		return "Engine\n" + Part::toString() + "\n" + m_partDesc->toString();

	return "Engine\n" + Part::toString() + "No Engine Desc";
}

//------------------------------------------------------------------------------

__forceinline float getLenght(const Vector3& v1, const Vector3& v2) {

	return (v1 - v2).length();
}

__forceinline float getLenghtOnTerrain(const Vector3& v1, const Vector3& v2) {

	return (Core::getSingletonPtr()->getTerrainHeightVec(v1) - Core::getSingletonPtr()->getTerrainHeightVec(v2)).length();
}

bool Engine::update(float deltaTime) {

	if (m_target != Vector3(-1.0f)) {

		switch (m_partDesc->isEngineDesc()->m_driveType) {

			case EngineDesc::DT_AIR:

				{
					static Vector3 v(Vector3::ZERO);

					v = Vector3::ZERO;

					if (getLenghtOnTerrain(m_parent->getPosition(), m_target) > 1.0f) {

						m_parent->leftOrRight(m_target - m_parent->getPosition(), m_yaw, 75.0f * deltaTime);

						m_parent->setOrientation(Quaternion(Radian(Degree(m_yaw)), Vector3::UNIT_Y));

						if (m_parent->getHeight() < 20.0f) {

							v.y = 6.0f;

						} else {

							v = m_parent->getDirection() * 50.0f;
						}

					} else {

						if (m_parent->getHeight() > 0.0f) {

							v.y = -3.0f;
						}
					}

					m_parent->setPosition(m_parent->getPosition() + v * deltaTime);
				}

				break;

			case EngineDesc::DT_GROUND:

				{
					float sinYaw = m_parent->leftOrRight(
						m_target - m_parent->getPosition(),
						m_yaw, 35 * deltaTime);

					m_parent->setOrientation(Quaternion(Radian(Degree(m_yaw)), Vector3::UNIT_Y));

					if (fabs(sinYaw) > 0.01)

						m_parent->setPosition(
							Core::getSingletonPtr()->getTerrainHeightVec(
							m_parent->getPosition() + m_parent->getDirection() * 2.5 * deltaTime));

					else

						m_parent->setPosition(
							Core::getSingletonPtr()->getTerrainHeightVec(
							m_parent->getPosition() + m_parent->getDirection() * 5 * deltaTime));

				}

		}
	}

	return true;
}

//------------------------------------------------------------------------------
