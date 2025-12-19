
//------------------------------------------------------------------------------
// PowerReactor.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Core.h"
#include "ObjectTemp.h"
#include "PowerReactor.h"

//------------------------------------------------------------------------------

PowerReactor::PowerReactor(ObjectTemp* parent) : Part(parent) {

	m_name = "Power Reactor #" + Core::getSingletonPtr()->getDataCounterStr();
	m_type = PT_POWER_REACTOR;
}

//------------------------------------------------------------------------------

string PowerReactor::toString() {

	if (m_partDesc)

		return "Power Reactor\n" + Part::toString() + "\n" + m_partDesc->toString();

	return "Power Reactor\n" + Part::toString() + "No Power Reactor Desc";
}

//------------------------------------------------------------------------------

bool PowerReactor::update(float deltaTime) {

	return true;
}

//------------------------------------------------------------------------------
