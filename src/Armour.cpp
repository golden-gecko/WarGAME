
//------------------------------------------------------------------------------
// Armour.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "PartDescManager.h"

#include "Armour.h"

//------------------------------------------------------------------------------

void Armour::setArmourDesc(string armourName){

	setArmourDesc((ArmourDesc*)PartDescManager::getSingletonPtr()->getByName(armourName));

}

//------------------------------------------------------------------------------

void Armour::setArmourDesc(ArmourDesc* armourDesc){

	if (armourDesc && (armourDesc->m_type == PartDesc::PDT_ARMOUR))

		m_armourDesc = armourDesc;

	else

		m_armourDesc = NULL;

}

//------------------------------------------------------------------------------
