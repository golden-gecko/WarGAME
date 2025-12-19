
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "EffectManager.h"

#include "Core.h"

//------------------------------------------------------------------------------

void Effect::create(const string& name) {

	m_particleSystem = Core::getSingletonPtr()->createParticleSystem(name);

	m_sceneNode = Core::getSingletonPtr()->createSceneNode();

	setEnabled(false);
}

//------------------------------------------------------------------------------

void Effect::destroy() {

	Core::getSingletonPtr()->destroyParticleSystem(m_particleSystem);
	Core::getSingletonPtr()->destroySceneNode(m_sceneNode);
}

//------------------------------------------------------------------------------
