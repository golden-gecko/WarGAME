
//------------------------------------------------------------------------------
// TeleporterDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class TeleporterDesc: public PartDesc {

		public:

			string	m_meshName;
			bool	m_castShadows;
			string	m_particleSystemName;

			TeleporterDesc(string name, float maxHitPoints, string meshName, bool castShadows, string particleSystemName)

				:	PartDesc(name, maxHitPoints),
					m_meshName(meshName),
					m_castShadows(castShadows),
					m_particleSystemName(particleSystemName) {
			
				m_type = PDT_TELEPORTER_DESC;
			}

	};
};

//------------------------------------------------------------------------------
