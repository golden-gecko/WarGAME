
//------------------------------------------------------------------------------
// VehicleDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "FortificationDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class VehicleDesc : public FortificationDesc {

		public:

			EngineDesc* m_engineDesc;

			VehicleDesc(	string name,
							ArmourDesc* armourDesc,
							BodyDesc* bodyDesc,
							EngineDesc* engineDesc,
							WeaponDesc* weaponDesc)

				:	FortificationDesc(name, armourDesc, bodyDesc, weaponDesc),
					m_engineDesc(engineDesc)
			
			{

				m_type = ODT_VEHICLE_DESC;
			
			}

	};

};

//------------------------------------------------------------------------------
