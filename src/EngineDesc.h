
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class EngineDesc: public PartDesc {

		protected:

			float m_maxFuel;
			float m_maxPower;

		public:

			EngineDesc(): PartDesc(PDT_ENGINE_DESC), m_maxFuel(0.0f), m_maxPower(0.0f) { }

			float getMaxFuel() {

				return m_maxFuel;
			}
			float getMaxPower() {

				return m_maxPower;
			}

			void setMaxFuel(float maxFuel) {

				m_maxFuel = maxFuel;
			}
			void setMaxPower(float maxPower) {

				m_maxPower = maxPower;
			}

			string toString() {

				static char str[256];

				sprintf(
					str,
					"engine desc\n  name - %s\n  max hit points - %.2f\n  max fuel - %.2f\n  max power - %.2f",
					m_name.c_str(),
					m_maxHitPoints,
					m_maxFuel,
					m_maxPower);

				return str;
			}

	};

};

//------------------------------------------------------------------------------
