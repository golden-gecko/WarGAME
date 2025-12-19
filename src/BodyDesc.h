
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartWithMeshDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class BodyDesc: public PartWithMeshDesc {

		public:

			BodyDesc(): PartWithMeshDesc(PDT_BODY_DESC) { }

			string toString() {

				static char str[256];

				sprintf(
					str,
					"body desc\n  name - %s\n  max hit points - %.2f\n  mesh name - %s\n  cast shadows - %s",
					m_name.c_str(),
					m_maxHitPoints,
					m_meshName.c_str(),
					(m_castShadows ? "true" : "false"));

				return str;
			}

	};

};

//------------------------------------------------------------------------------
