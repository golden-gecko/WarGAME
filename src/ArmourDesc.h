
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class ArmourDesc: public PartDesc {

		protected:

			float m_defense;

		public:

			ArmourDesc(): PartDesc(PDT_ARMOUR_DESC), m_defense(0.0f) { }

			float getDefense() {
				
				return m_defense;
			}

			void setDefense(float defense) {

				m_defense = defense;
			}

			string toString() {

				static char str[256];

				sprintf(
					str,
					"armour desc\n  name - %s\n  max hit points - %.2f\n  defense - %.2f",
					m_name.c_str(),
					m_maxHitPoints,
					m_defense);

				return str;
			}

	};

};

//------------------------------------------------------------------------------
