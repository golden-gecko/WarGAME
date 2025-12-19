
//------------------------------------------------------------------------------
// Shield.h
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Core.h"
#include "Shield.h"

//------------------------------------------------------------------------------

Shield::Shield(ObjectTemp* parent)

	:	Body(parent),
		m_timeSinceLastChange(0.0f),
		m_timeToNextChange(0.0f),
		m_pulseTime(0.0f),
		m_pulseMode(1.0f)

{
	m_name = "Energy Shield #" + Core::getSingletonPtr()->getDataCounterStr();
	m_type = PT_ENERGY_SHIELD;
	m_sceneNode = m_parent->m_body->m_sceneNode->createChildSceneNode(Core::getSingletonPtr()->getDataCounterStr());

	for (int i = 0; i < 3; i++)

		m_rot[0] = rand() % 2 ? 1.0f : -1.0f;

}

//------------------------------------------------------------------------------

void Shield::setDesc(PartDesc* partDesc) {

	Core::getSingletonPtr()->destroyEntity(m_entity);

	if (partDesc && partDesc->isEnergyShieldDesc()) {

		Part::setDesc(partDesc);

		m_entity = Core::getSingletonPtr()->createEntity(m_partDesc->isEnergyShieldDesc()->m_meshName);
		m_entity->setCastShadows(false);
		m_entity->setUserAny(Any(this));

		m_sceneNode->attachObject(m_entity);
		m_sceneNode->setScale(Vector3(m_parent->getBoundingRadius() / m_entity->getBoundingRadius() * 2.0f));

		m_pulseMaterialTech = m_entity->getSubEntity(0)->getMaterial()->getTechnique(0);

	} else {

		Part::setDesc(NULL);

		m_entity = NULL;
	}
}

//------------------------------------------------------------------------------

bool Shield::update(float deltaTime) {

	if (m_partDesc) {

		// Regenerate Hit Points.

		if (m_hitPoints < getMaxHitPoints())

			m_hitPoints += getRegenerationRate() * deltaTime;

		else if (m_hitPoints > getMaxHitPoints())

			m_hitPoints = getMaxHitPoints();

		// Pulse.

		if (m_pulseTime >= 1.0f)

			m_pulseMode = -1.0f;

		else if (m_pulseTime <= 0.0f)

			m_pulseMode = 1.0f;

		m_pulseTime += deltaTime * m_pulseMode;

		m_pulseMaterialTech->getPass(0)->setAmbient(ColourValue(1.0f, 0.5f, 0.5f, 0.15f + m_pulseTime / 8.0f));
		m_pulseMaterialTech->getPass(0)->setDiffuse(ColourValue(0.0f, 0.0f, 0.0f, 0.15f + m_pulseTime / 8.0f));
		m_pulseMaterialTech->getPass(1)->setAmbient(ColourValue(1.0f, 1.0f, 0.5f, 0.05f + m_pulseTime / 8.0f));
		m_pulseMaterialTech->getPass(1)->setDiffuse(ColourValue(0.0f, 0.0f, 0.0f, 0.05f + m_pulseTime / 8.0f));

		// Rotate at random.

		if (m_timeSinceLastChange >= m_timeToNextChange) {

			m_timeSinceLastChange = 0.0f;
			m_timeToNextChange = (rand() % 2000 + 1000) / 1000.0f;

			m_rot[rand() % 3] = rand() % 2 ? 1.0f : -1.0f;

		} else {

			m_timeSinceLastChange += deltaTime;

			m_sceneNode->rotate(Vector3(m_rot[0], m_rot[1], m_rot[2]), Radian(Degree(deltaTime * 15.0f)));
		}
	}

	return true;
}

//------------------------------------------------------------------------------
