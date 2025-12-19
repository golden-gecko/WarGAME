
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Shield.h"

#include "Body.h"
#include "Object.h"

//------------------------------------------------------------------------------

void Shield::setParent(Object* parent) {

	PartWithMesh::setParent(parent);

	if (m_parent && m_parent->getBody())

		m_sceneNode->scale(
			m_parent->getBody()->getBoundingRadius() / getBoundingRadius() * 2.0f,
			m_parent->getBody()->getBoundingRadius() / getBoundingRadius() * 2.0f,
			m_parent->getBody()->getBoundingRadius() / getBoundingRadius() * 2.0f);
}

//------------------------------------------------------------------------------

void Shield::setPartDesc(PartDesc* partDesc) {

	PartWithMesh::setPartDesc(partDesc);

	if (m_shieldDesc)

		m_pulseMaterialTech = m_entity->getSubEntity(0)->getMaterial()->getTechnique(0);
}

//------------------------------------------------------------------------------

string Shield::toString() {

	static char str[256];

	sprintf(
		str,
		"shield\n  name - %s (installed at %s)\n  hit points - %.2f/%.2f",
		m_name.c_str(),
		m_parent->getName().c_str(),
		m_hitPoints,
		getMaxHitPoints());

	return str;
}

//------------------------------------------------------------------------------

bool Shield::update(float deltaTime) {

	if (m_shieldDesc) {

		// Pulse.

		if (m_pulseTime >= 1.0f)

			m_pulseMode = -1.0f;

		else if (m_pulseTime <= 0.0f)

			m_pulseMode = 1.0f;

		m_pulseTime += deltaTime * m_pulseMode;

		m_pulseMaterialTech->getPass(0)->setAmbient(Ogre::ColourValue(1.0f, 0.5f, 0.5f, 0.15f + m_pulseTime / 8.0f));
		m_pulseMaterialTech->getPass(0)->setDiffuse(Ogre::ColourValue(0.0f, 0.0f, 0.0f, 0.15f + m_pulseTime / 8.0f));
		m_pulseMaterialTech->getPass(1)->setAmbient(Ogre::ColourValue(1.0f, 1.0f, 0.5f, 0.05f + m_pulseTime / 8.0f));
		m_pulseMaterialTech->getPass(1)->setDiffuse(Ogre::ColourValue(0.0f, 0.0f, 0.0f, 0.05f + m_pulseTime / 8.0f));

		return true;
	}

	return false;
}

//------------------------------------------------------------------------------
