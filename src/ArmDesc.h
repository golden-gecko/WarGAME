
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartWithMeshDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class ArmDesc: public PartWithMeshDesc {

		protected:

			float m_maxEnergyUsed;

		public:

			ArmDesc(): PartWithMeshDesc(PDT_ARM_DESC), m_maxEnergyUsed(0.0f) { }

			float getMaxEnergyUsed() {

				return m_maxEnergyUsed;
			}

			void setMaxEnergyUsed(float maxEnergyUsed) {

				m_maxEnergyUsed = maxEnergyUsed;
			}

			string toString() {

				static char str[256];

				sprintf(
					str,
					"weapon desc\n  name - %s\n  max hit points - %.2f",
					m_name.c_str(),
					m_maxHitPoints);

				return str;
			}
	};
};

//------------------------------------------------------------------------------
