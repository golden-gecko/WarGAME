
//------------------------------------------------------------------------------
// Shield.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Body.h"
#include "EnergyShieldDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Shield: public Body {

		protected:

			float	m_timeSinceLastChange;
			float	m_timeToNextChange;
			float	m_rot[3];

			Technique*	m_pulseMaterialTech;
			float		m_pulseTime;
			float		m_pulseMode;

		public:

			Shield(ObjectTemp* parent);

			float getRegenerationRate() {

				if (m_partDesc)

					return m_partDesc->isEnergyShieldDesc()->m_regenerationRate;

				return 0.0f;
			}

			virtual void setDesc(PartDesc* partDesc = NULL);

			virtual bool update(float deltaTime);

	};
};

//------------------------------------------------------------------------------
