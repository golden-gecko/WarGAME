
//------------------------------------------------------------------------------
// PowerReactor.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "Core.h"

#include "PartDescManager.h"

#include "PowerReactor.h"

//------------------------------------------------------------------------------

void PowerReactor::set(string powerReactorName){

	set((PowerReactorDesc*)PartDescManager::getSingletonPtr()->getByName(powerReactorName));

}

//------------------------------------------------------------------------------

void PowerReactor::set(PowerReactorDesc* powerReactorDesc){

	if (powerReactorDesc && (powerReactorDesc->m_type == PartDesc::PDT_POWER_REACTOR))

		m_powerReactorDesc = powerReactorDesc;
	
	else

		m_powerReactorDesc = NULL;

}

//------------------------------------------------------------------------------
