
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartWithMesh.h"

#include "TeleporterDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Teleporter: public PartWithMesh {

		public:

			Teleporter(): PartWithMesh(PT_TELEPORTER) { }

			TeleporterDesc* getTeleporterDesc() {

				return m_teleporterDesc;
			}

			string toString();

			bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
