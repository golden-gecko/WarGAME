
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class StorageDesc: public PartDesc {

		protected:

			WORD	m_maxAmmunition;
			float	m_maxEnergy;
			float	m_maxFuel;

		public:

			StorageDesc()
				:	PartDesc(PDT_STORAGE_DESC),
					m_maxAmmunition(0),
					m_maxEnergy(0.0f),
					m_maxFuel(0.0f) { }

			WORD getMaxAmmunition() {

				return m_maxAmmunition;
			}
			float getMaxEnergy() {

				return m_maxEnergy;
			}
			float getMaxFuel() {

				return m_maxFuel;
			}

			void setMaxAmmunition(WORD maxAmmunition) {

				m_maxAmmunition = maxAmmunition;
			}
			void setMaxEnergy(float maxEnergy) {

				m_maxEnergy = maxEnergy;
			}
			void setMaxFuel(float maxFuel) {

				m_maxFuel = maxFuel;
			}

	};

};

//------------------------------------------------------------------------------
