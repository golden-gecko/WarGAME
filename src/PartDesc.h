
//------------------------------------------------------------------------------
// PartDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Resource.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class PartDesc: public Resource {

		protected:

			float	m_maxHitPoints;
			float	m_mass;

		public:
 
			PartDesc(): m_maxHitPoints(0.0f), m_mass(0.0f) { }

			float getMaxHitPoints(){

				return m_maxHitPoints;
			}

			float getMass() {

				return m_mass;
			}

			void setMaxHitPoints(float maxHitPoints) {

				m_maxHitPoints = maxHitPoints;
			}

			void setMass(float mass) {

				m_mass = mass;
			}

			virtual string toString() {

				char str[512];

				sprintf(
					str,
					"\
					  Name %s\n\
					  Max Hit Points %.0f",
					m_name.c_str(),
					m_maxHitPoints);

				return str;
			}

	};

};

//------------------------------------------------------------------------------
