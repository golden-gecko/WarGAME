
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Resource.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class PartDesc: public Resource {

		public:

			enum PartDescType {

				PDT_ARM_DESC		= 0x0001,
				PDT_ARMOUR_DESC		= 0x0002,
				PDT_BODY_DESC		= 0x0004,
				PDT_ENGINE_DESC		= 0x0008,
				PDT_EXPLOSIVE_DESC	= 0x0010,
				PDT_REACTOR_DESC	= 0x0020,
				PDT_SHIELD_DESC		= 0x0040,
				PDT_STORAGE_DESC	= 0x0080,
				PDT_TELEPORTER_DESC	= 0x0100,
				PDT_WEAPON_DESC		= 0x0200

			};

		protected:

			PartDescType	m_type;
			float			m_maxHitPoints;

		public:
 
			PartDesc(PartDescType type): m_type(type), m_maxHitPoints(0.0f) { }

			PartDescType getType() {

				return m_type;
			}
			float getEnergyCost() {

				return m_maxHitPoints * pow(1.01f, m_maxHitPoints);
			}
			float getMaxHitPoints(){

				return m_maxHitPoints;
			}

			void setMaxHitPoints(float maxHitPoints) {

				m_maxHitPoints = maxHitPoints;
			}

	};

};

//------------------------------------------------------------------------------
