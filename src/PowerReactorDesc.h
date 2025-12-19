
//------------------------------------------------------------------------------
// PowerReactorDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "PartDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class PowerReactorDesc : public PartDesc {

		public:

			float m_maxEnergyStored;
			float m_maxEnergyProduced;

			PowerReactorDesc(	string name,
								float maxHitPoints,
								float maxEnergyStored,
								float maxEnergyProduced)

				:	PartDesc(name, maxHitPoints),
					m_maxEnergyStored(maxEnergyStored),
					m_maxEnergyProduced(maxEnergyProduced)

			{

				m_type = PDT_POWER_REACTOR_DESC;

			}

			virtual string toString() {

				char text[512];

				sprintf(
					text,
					"\
					Power Reactor Desc\n\
					%s\n\
					  Max Energy Stored   %.2f\n\
					  Max Energy Produced %.2f",
					PartDesc::toString().c_str(),
					m_maxEnergyStored,
					m_maxEnergyProduced);

				return text;

			}

	};

};

//------------------------------------------------------------------------------
