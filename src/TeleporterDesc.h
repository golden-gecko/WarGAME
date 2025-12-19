
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartWithMeshDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class TeleporterDesc: public PartWithMeshDesc {

		public:

			TeleporterDesc(): PartWithMeshDesc(PDT_TELEPORTER_DESC) { }

			string toString() {

				static char str[256];

				sprintf(
					str,
					"teleporter desc\n  name - %s\n  max hit points - %.2f",
					m_name.c_str(),
					m_maxHitPoints);

				return str;
			}

	};

};

//------------------------------------------------------------------------------
