
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Armour.h"

//------------------------------------------------------------------------------

string Armour::toString() {

	static char str[256];

	sprintf(
		str,
		"armour\n  name - %s\n  hit points - %.2f/%.2f\n  energy cost - %.2f",
		m_name.c_str(),
		m_hitPoints,
		getMaxHitPoints(),
		getEnergyCost());

	return str;
}

//------------------------------------------------------------------------------

bool Armour::update(float deltaTime) {

	return Part::update(deltaTime);
}

//------------------------------------------------------------------------------
