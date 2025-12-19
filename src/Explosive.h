
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Part.h"

#include "ExplosiveDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Explosive: public Part {

		public:

			enum ExplosiveType {

				ET_NONE			= 0x00,
				ET_DISTANCE		= 0x01,
				ET_MANUAL		= 0x02,
				ET_HIT			= 0x04

			};

		protected:

			ExplosiveType m_explosiveType;

		public:

			Explosive(): Part(PT_EXPLOSIVE), m_explosiveType(ET_NONE) { }

			ExplosiveDesc* getExplosiveDesc() {

				return m_explosiveDesc;
			}
			ExplosiveType getExplosiveType() {

				return m_explosiveType;
			}

			void setExplosiveType(ExplosiveType explosiveType) {

				m_explosiveType = explosiveType;
			}

			void explode();

			string toString();

			bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
