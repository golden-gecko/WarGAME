
//------------------------------------------------------------------------------
// FortificationDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ObjectDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class FortificationDesc: public BuildingDesc {

		public:

			WeaponDesc*	m_weaponDesc;

			FortificationDesc(	string				name,
								ArmourDesc*			armourDesc,
								BodyDesc*			bodyDesc,
								EnergyShieldDesc*	energyShieldDesc,
								WeaponDesc*			weaponDesc)

				:	BuildingDesc(	name,
									armourDesc,
									bodyDesc,
									energyShieldDesc),

					m_weaponDesc(weaponDesc)
			{
				m_type = ODT_FORTIFICATION_DESC;
			}

	};

};

//------------------------------------------------------------------------------
