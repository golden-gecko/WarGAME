
//------------------------------------------------------------------------------
// VehicleDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "FortificationDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class VehicleDesc : public FortificationDesc {

		public:

			EngineDesc* m_engineDesc;


			VehicleDesc(	string				name,
							ArmourDesc*			armourDesc,
							BodyDesc*			bodyDesc,
							EnergyShieldDesc*	energyShieldDesc,
							EngineDesc*			engineDesc,
							WeaponDesc*			weaponDesc)

				:	FortificationDesc(	name,
										armourDesc,
										bodyDesc,
										energyShieldDesc,
										weaponDesc),

					m_engineDesc(engineDesc)
			{
				m_type = ODT_VEHICLE_DESC;
			}

	};

};

//------------------------------------------------------------------------------
