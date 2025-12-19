
//------------------------------------------------------------------------------
// ArmourDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "PartDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class ArmourDesc: public PartDesc {

		public:

			float m_defense;

			ArmourDesc(string name, float maxHitPoints, float defense)

				:	PartDesc(name, maxHitPoints),
					m_defense(defense)

			{
				m_type = PDT_ARMOUR_DESC;
			}

			virtual string toString() {

				char str[512];

				sprintf(
					str,
					"\
					Armour Desc\n\
					%s\n\
					  Defense %.2f",
					PartDesc::toString().c_str(),
					m_defense);

				return str;
			}

	};
};

//------------------------------------------------------------------------------
