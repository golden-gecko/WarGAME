
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Part.h"

#include "ArmourDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Armour: public Part {

		public:

			Armour(): Part(PT_ARMOUR) { }

			ArmourDesc* getArmourDesc() {

				return m_armourDesc;
			}

			string toString();

			bool update(float deltaTime);

	};
};

//------------------------------------------------------------------------------
