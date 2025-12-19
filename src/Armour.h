
//------------------------------------------------------------------------------
// Armour.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "ArmourDesc.h"
#include "Part.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Armour : public Part {

		public:

			ArmourDesc* m_armourDesc;

			Armour(Object* parent) : Part(parent), m_armourDesc(NULL) { }

			void setArmourDesc(string armourName);
			void setArmourDesc(ArmourDesc* armourDesc);

			virtual string toString(){

				char text[512];

				return text;

			}

	};

};

//------------------------------------------------------------------------------
