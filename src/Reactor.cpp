
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Reactor.h"

#include "Object.h"
#include "Player.h"

//------------------------------------------------------------------------------

void Reactor::setParent(Object* parent) {

	if (m_parent && (m_parent->getPlayer() == NULL)) {

		m_parent->getPlayer()->decreaseMaxEnergyStored(m_reactorDesc->getMaxEnergyStored());
		m_parent->getPlayer()->decreaseEnergyProduced(m_reactorDesc->getMaxEnergyProduced());
		m_parent->getPlayer()->decreaseMaxEnergyProduced(m_reactorDesc->getMaxEnergyProduced());
	}

	Part::setParent(parent);

	if (m_parent && m_parent->getPlayer()) {

		m_parent->getPlayer()->increaseMaxEnergyStored(m_reactorDesc->getMaxEnergyStored());
		m_parent->getPlayer()->increaseEnergyProduced(m_reactorDesc->getMaxEnergyProduced());
		m_parent->getPlayer()->increaseMaxEnergyProduced(m_reactorDesc->getMaxEnergyProduced());
	}
}

//------------------------------------------------------------------------------

string Reactor::toString() {

	static char str[256];

	sprintf(
		str,
		"reactor\n  name - %s (installed at %s)\n  hit points - %.2f/%.2f",
		m_name.c_str(),
		m_parent->getName().c_str(),
		m_hitPoints,
		getMaxHitPoints());

	return str;
}

//------------------------------------------------------------------------------

bool Reactor::update(float deltaTime) {

	return Part::update(deltaTime);
}

//------------------------------------------------------------------------------
