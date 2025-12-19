
//------------------------------------------------------------------------------
// PowerPlant.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Core.h"
#include "PowerPlant.h"

//------------------------------------------------------------------------------

PowerPlant::PowerPlant() : m_powerReactor(NULL) {

	m_name = "Power Plant #" + Core::getSingletonPtr()->getDataCounterStr();
	m_type = OT_POWER_PLANT;
	m_powerReactor = new PowerReactor(this);
}

//------------------------------------------------------------------------------

PowerPlant::~PowerPlant() {

	delete m_powerReactor;
}

//------------------------------------------------------------------------------

string PowerPlant::toString() {

	return Building::toString() + "\n\n" + m_powerReactor->toString();
}

//------------------------------------------------------------------------------

bool PowerPlant::update(float deltaTime) {

	return Building::update(deltaTime) && m_powerReactor->update(deltaTime);
}

//------------------------------------------------------------------------------
