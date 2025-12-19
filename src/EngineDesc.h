
//------------------------------------------------------------------------------
// EngineDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "PartDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class EngineDesc : public PartDesc {

		public:

			enum DriveType {

				// Unit can move fly the air and land on the ground surface.
				DT_AIR		= 0x01,
				// Unit can move on the ground surface.
				DT_GROUND	= 0x02

			};

			float		m_maxFuel;
			float		m_power;
			DriveType	m_driveType;

			EngineDesc(	string name,
						float maxHitPoints,
						float maxFuel,
						float power,
						DriveType driveType)

				:	PartDesc(name, maxHitPoints),
					m_maxFuel(maxFuel),
					m_power(power),
					m_driveType(driveType)

			{
				m_type = PDT_ENGINE_DESC;
			}

			virtual string toString() {

				char str[512];

				sprintf(str, "");

				return str;
			}

	};

};

//------------------------------------------------------------------------------
