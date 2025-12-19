
//------------------------------------------------------------------------------
// BuildingDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ArmourDesc.h"
#include "EnergyShieldDesc.h"
#include "ObjectDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class BuildingDesc: public ObjectDesc {

		public:

			ArmourDesc*			m_armourDesc;
			EnergyShieldDesc*	m_energyShieldDesc;

			BuildingDesc(	string				name,
							ArmourDesc*			armourDesc,
							BodyDesc*			bodyDesc,
							EnergyShieldDesc*	energyShieldDesc)

				:	ObjectDesc(	name,
								bodyDesc),

					m_armourDesc(armourDesc),
					m_energyShieldDesc(energyShieldDesc)
			{
				m_type = ODT_BUILDING_DESC;
			}

			virtual string toString() {

				return ObjectDesc::toString() + "\n\n" + m_armourDesc->toString();
			}

	};
};

//------------------------------------------------------------------------------
