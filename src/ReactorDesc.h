
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class ReactorDesc: public PartDesc {

		protected:

			float m_maxEnergyStored;
			float m_maxEnergyProduced;

		public:

			ReactorDesc(): PartDesc(PDT_REACTOR_DESC), m_maxEnergyStored(0.0f), m_maxEnergyProduced(0.0f) { }

			float getMaxEnergyStored() {

				return m_maxEnergyStored;
			}
			float getMaxEnergyProduced() {

				return m_maxEnergyProduced;
			}

			void setMaxEnergyStored(float maxEnergyStored) {

				m_maxEnergyStored = maxEnergyStored;
			}
			void setMaxEnergyProduced(float maxEnergyProduced) {

				m_maxEnergyProduced = maxEnergyProduced;
			}

			string toString() {

				static char str[256];

				sprintf(
					str,
					"reactor desc\n  name - %s\n  max hit points - %.2f\n  max energy stored - %.2f\n  max energy produced - %.2f",
					m_name.c_str(),
					m_maxHitPoints,
					m_maxEnergyStored,
					m_maxEnergyProduced);

				return str;
			}

	};

};

//------------------------------------------------------------------------------
