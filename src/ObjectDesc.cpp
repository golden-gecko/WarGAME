
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ObjectDesc.h"

#include "ArmourDesc.h"
#include "BodyDesc.h"
#include "EngineDesc.h"
#include "ExplosiveDesc.h"
#include "ReactorDesc.h"
#include "ShieldDesc.h"
#include "TeleporterDesc.h"
#include "WeaponDesc.h"

//------------------------------------------------------------------------------

float ObjectDesc::getEnergyCost() {

	return
		(m_armourDesc ? m_armourDesc->getEnergyCost() : 0.0f) + 
		(m_bodyDesc ? m_bodyDesc->getEnergyCost() : 0.0f) + 
		(m_engineDesc ? m_engineDesc->getEnergyCost() : 0.0f) + 
		(m_explosiveDesc ? m_explosiveDesc->getEnergyCost() : 0.0f) + 
		(m_reactorDesc ? m_reactorDesc->getEnergyCost() : 0.0f) + 
		(m_shieldDesc ? m_shieldDesc->getEnergyCost() : 0.0f) + 
		(m_teleporterDesc ? m_teleporterDesc->getEnergyCost() : 0.0f) + 
		(m_weaponDesc ? m_weaponDesc->getEnergyCost() : 0.0f);
}

//------------------------------------------------------------------------------
