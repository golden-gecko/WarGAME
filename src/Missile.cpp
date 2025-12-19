
//------------------------------------------------------------------------------
// Missile.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Core.h"
#include "Fortification.h"
#include "Missile.h"
#include "Vehicle.h"

//------------------------------------------------------------------------------

Missile::Missile(ObjectTemp* parent)
	:	m_parent(parent),
		m_explosion(Core::getSingletonPtr()->createParticleSystem("fire_explosion"))

{
	m_name = "Missile #" + Core::getSingletonPtr()->getDataCounterStr();
	m_type = OT_MISSILE;
	m_body->m_sceneNode->attachObject(m_explosion);
	m_explosion->getEmitter(0)->setEnabled(false);
}

//------------------------------------------------------------------------------

Missile::~Missile() {

	Core::getSingletonPtr()->destroyParticleSystem(m_explosion);
}

//------------------------------------------------------------------------------

bool Missile::update(float deltaTime) {

	switch (m_state) {

		case OS_IDLE:

			{
				RaySceneQueryResult result = Core::getSingletonPtr()->whatWouldHit(
					getWorldCenter(), getDirection());

				bool hit = false;
				float distance = 0.0f;

				if (getPosition().y <= Core::getSingletonPtr()->getTerrainHeight(getPosition().x, getPosition().z)) {

					m_state = OS_DEAD;
					m_body->m_sceneNode->detachObject(m_body->m_entity);
					m_explosion->getEmitter(0)->setEnabled(true);

					if (m_parent->m_state != ObjectTemp::OS_DEAD) {

						if (m_parent->isFortification())

							(m_parent->isFortification()->m_terrainHits)++;

						else if (m_parent->isVehicle())

							(m_parent->isVehicle()->m_terrainHits)++;

					}

					break;

				}

				for (RaySceneQueryResult::iterator itr = result.begin(); itr != result.end(); itr++)

					if (itr->movable && (itr->movable->getUserAny().isEmpty() == false)) {

						ObjectTemp* o = Core::getSingletonPtr()->ogreAnyToObject(itr->movable->getUserAny());

						if (o && (o->m_state != OS_DEAD) && (o != this) && (o != m_parent) && (itr->distance <= 50.0f * deltaTime)) {

							hit = true;
							distance = itr->distance;

							o->decreaseHitPoints(5.0f);

							m_state = OS_DEAD;
							m_body->m_sceneNode->detachObject(m_body->m_entity);
							m_explosion->getEmitter(0)->setEnabled(true);

							if (m_parent->m_state != ObjectTemp::OS_DEAD) {

								if (m_parent->isFortification())

									(m_parent->isFortification()->m_objectHits)++;

								else if (m_parent->isVehicle())

									(m_parent->isVehicle()->m_objectHits)++;

							}

							break;
						}
					}

				if (hit)

					setPosition(getPosition() + getDirection() * distance);

				else

					setPosition(getPosition() + getDirection() * 50.0f * deltaTime);

				static AxisAlignedBox box;

				Core::getSingletonPtr()->getSceneManager()->getOption("Size", &box);

				if (getPosition().x < box.getMinimum().x || getPosition().y < box.getMinimum().y || getPosition().z < box.getMinimum().z || getPosition().x > box.getMaximum().x || getPosition().y > box.getMaximum().y || getPosition().z > box.getMaximum().z) {

					m_body->m_sceneNode->detachObject(m_body->m_entity);
					m_explosion->getEmitter(0)->setEnabled(false);
				}

				break;
			}

		case OS_DEAD:

			if ((m_explosion->getEmitter(0)->getEnabled() == false) && (m_explosion->getNumParticles() == 0))

				return false;

			return true;

	} // switch (m_state)

	return true;
}

//------------------------------------------------------------------------------
