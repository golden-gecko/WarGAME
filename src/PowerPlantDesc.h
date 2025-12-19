
//------------------------------------------------------------------------------
// PowerPlantDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "BuildingDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class PowerPlantDesc: public BuildingDesc {

		public:

			ReactorDesc* m_powerReactorDesc;

			PowerPlantDesc(
				string				name,
				ArmourDesc*			armourDesc,
				BodyDesc*			bodyDesc,
				EnergyShieldDesc*	energyShieldDesc,
				ReactorDesc*	powerReactorDesc)

				:	BuildingDesc(name, armourDesc, bodyDesc, energyShieldDesc),
					m_powerReactorDesc(powerReactorDesc)
			
			{
				m_type = ODT_POWER_PLANT_DESC;
			}

	};

};

//------------------------------------------------------------------------------
