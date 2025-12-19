
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartWithMesh.h"

#include "BodyDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Body: public PartWithMesh {

		public:

			Body(): PartWithMesh(PT_BODY) { }

			BodyDesc* getBodyDesc() {

				return m_bodyDesc;
			}

			string toString();

			bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
