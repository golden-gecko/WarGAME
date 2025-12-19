
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Body.h"
#include "Object.h"

//------------------------------------------------------------------------------

string Body::toString() {

	static char str[256];

	sprintf(
		str,
		"body\n  name - %s (installed at %s)\n  hit points - %.2f/%.2f\n  energy cost - %.2f",
		m_name.c_str(),
		m_parent->getName().c_str(),
		m_hitPoints,
		getMaxHitPoints(),
		getEnergyCost());

	return str;
}

//------------------------------------------------------------------------------

bool Body::update(float deltaTime) {

	return Part::update(deltaTime);
}

//------------------------------------------------------------------------------
