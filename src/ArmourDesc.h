
//------------------------------------------------------------------------------
// ArmourDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "PartDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class ArmourDesc : public PartDesc {

		public:

			float m_defense;

			ArmourDesc(string name, float maxHitPoints, float defense)

				:	PartDesc(name, maxHitPoints),
					m_defense(defense)

			{

				m_type = PDT_ARMOUR;

			}

			virtual string toString(){

				char text[512];

				sprintf(
					text,
					"\
					%s\n\
					Defense Factor      %.2f",
					PartDesc::toString().c_str(),
					m_defense);

				return text;

			}

	};

};

//------------------------------------------------------------------------------
