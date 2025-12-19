
//------------------------------------------------------------------------------
// Armour.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Armour.h"
#include "Core.h"
#include "ObjectTemp.h"

//------------------------------------------------------------------------------

Armour::Armour(ObjectTemp* parent) : Part(parent) {

	m_name = "Armour #" + Core::getSingletonPtr()->getDataCounterStr();
	m_type = PT_ARMOUR;
}

//------------------------------------------------------------------------------

void Armour::set(PartDesc* partDesc) {

	if (partDesc && partDesc->isArmourDesc())

		Part::setDesc(partDesc);

	else

		Part::setDesc(NULL);

}

//------------------------------------------------------------------------------

string Armour::toString() {

	if (m_partDesc)

		return "Armour\n" + Part::toString() + "\n" + m_partDesc->toString();

	return "Armour\n" + Part::toString() + "No Armour Desc";
}

//------------------------------------------------------------------------------

bool Armour::update(float deltaTime) {

	return true;
}

//------------------------------------------------------------------------------
