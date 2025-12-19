
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {
	
	class ExplosiveDesc: public PartDesc {

		protected:

			float m_damage;
			float m_radius;

		public:

			ExplosiveDesc(): PartDesc(PDT_EXPLOSIVE_DESC), m_damage(0.0f), m_radius(0.0f) { }

			float getDamage() {

				return m_damage;
			}
			float getRadius() {

				return m_radius;
			}

			void setDamage(float damage) {

				m_damage = damage;
			}
			void setRadius(float radius) {

				m_radius = radius;
			}

			string toString() {

				static char str[256];

				sprintf(
					str,
					"explosive desc\n  name - %s\n  max hit points - %.2f\n  damage - %.2f\n  radius - %.2f",
					m_name.c_str(),
					m_maxHitPoints,
					m_damage,
					m_radius);

				return str;
			}

	};

};

//------------------------------------------------------------------------------
