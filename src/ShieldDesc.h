
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartWithMeshDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class ShieldDesc: public PartWithMeshDesc {

		protected:

			float m_regenerationRate;

		public:

			ShieldDesc(): PartWithMeshDesc(PDT_SHIELD_DESC), m_regenerationRate(0.0f) { }

			float getRegenerationRate() {

				return m_regenerationRate;
			}

			void setRegenerationRate(float regenerationRate) {

				m_regenerationRate = regenerationRate;
			}

			string toString() {

				static char str[256];

				sprintf(
					str,
					"shield desc\n  name - %s\n  max hit points - %.2f\n  regeneration rate - %.2f",
					m_name.c_str(),
					m_maxHitPoints,
					m_regenerationRate);

				return str;
			}

	};

};

//------------------------------------------------------------------------------
