
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ResourceManager.h"

#include "Armour.h"
#include "Body.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	namespace PartManager {

		class ArmourManager: public ResourceManager<Armour> {

		};

		class BodyManager: public ResourceManager<Body> {

		};

	};

};

//------------------------------------------------------------------------------
