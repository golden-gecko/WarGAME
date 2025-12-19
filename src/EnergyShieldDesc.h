
//------------------------------------------------------------------------------
// EnergyShieldDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "PartDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class EnergyShieldDesc: public PartDesc {

		public:

			string	m_meshName;
			float	m_regenerationRate;

			EnergyShieldDesc(	string name,
								float maxHitPoints,
								string meshName,
								float regenerationRate)

				:	PartDesc(name, maxHitPoints),
					m_meshName(meshName),
					m_regenerationRate(regenerationRate) {

				m_type = PDT_ENERGY_SHIELD_DESC;
			}

			virtual string toString() {

				char text[512];

				sprintf(
					text,
					"\
					Energy Shield Desc\n\
					%s\n\
					  Regeneration Rate %.2f",
					PartDesc::toString().c_str(),
					m_regenerationRate);

				return text;
			}

	};
};

//------------------------------------------------------------------------------
