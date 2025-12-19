
//------------------------------------------------------------------------------
// Armour.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "ArmourDesc.h"
#include "Part.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Armour: public Part {

		public:

			Armour(ObjectTemp* parent);

			virtual void set(PartDesc* partDesc);

			virtual string toString();

			virtual bool update(float deltaTime);

	};
};

//------------------------------------------------------------------------------
