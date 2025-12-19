
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "Part.h"

#include "ExplosiveDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Explosive: public Part {

		public:

			ExplosiveDesc* m_explosiveDesc;

		public:

			Explosive(): m_explosiveDesc(NULL) {

			}

	};

};

//------------------------------------------------------------------------------
