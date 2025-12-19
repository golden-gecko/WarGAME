
//------------------------------------------------------------------------------
// Weapon.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Part.h"
#include "WeaponDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Weapon: public Body {

		public:

			enum WeaponFlag {

				WF_NONE			= 0x00,
				WF_FIRE_AT_WILL	= 0x01,
				WF_HOLD_FIRE	= 0x02,

			};

			float		m_yaw;
			float		m_pitch;
			float		m_reloadTime;
			int			m_ammunition;
			ObjectTemp*		m_target;
			WeaponFlag	m_flag;

		public:

			Weapon(ObjectTemp* parent);

			void attack(ObjectTemp* target) {

				m_target = target;
			}

			void attack(Vector3 position) {

			}

			bool fire();

			void stop() {

				m_target = NULL;
			}

			virtual void setDesc(PartDesc* partDesc = NULL);

			virtual string toString();

			virtual bool update(float deltaTime);

	};
};

//------------------------------------------------------------------------------
