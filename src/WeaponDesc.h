
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartWithMeshDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class WeaponDesc: public PartWithMeshDesc {

		protected:

			float	m_maxPower;
			float	m_maxReloadTime;
			float	m_turnSpeed;
			float	m_maxYaw;
			float	m_maxPitch;
			float	m_maxAmmunition;

		public:

			WeaponDesc()
				:	PartWithMeshDesc(PDT_WEAPON_DESC),
					m_maxReloadTime(0.0f),
					m_turnSpeed(0.0f),
					m_maxYaw(0.0f),
					m_maxPitch(0.0f),
					m_maxPower(0.0f),
					m_maxAmmunition(0.0f) { }

			float getMaxPower() {

				return m_maxPower;
			}
			float getMaxReloadTime() {

				return m_maxReloadTime;
			}
			float getTurnSpeed() {

				return m_turnSpeed;
			}
			float getMaxYaw() {

				return m_maxYaw;
			}
			float getMaxPitch() {

				return m_maxPitch;
			}
			float getMaxAmmunition() {

				return m_maxAmmunition;
			}

			void setMaxPower(float maxPower) {

				m_maxPower = maxPower;
			}
			void setMaxReloadTime(float maxReloadTime) {

				m_maxReloadTime = maxReloadTime;
			}
			void setTurnSpeed(float turnSpeed) {

				m_turnSpeed = turnSpeed;
			}
			void setMaxYaw(float maxYaw) {

				m_maxYaw = maxYaw;
			}
			void setMaxPitch(float maxPitch) {

				m_maxPitch = maxPitch;
			}
			void setMaxAmmunition(float maxAmmunition) {

				m_maxAmmunition = maxAmmunition;
			}

			string toString() {

				static char str[256];

				sprintf(
					str,
					"weapon desc\n  name - %s\n  max hit points - %.2f\n  max power - %.2f\n  max reload time - %.2f\n  turn speed - %.2f\n  max yaw - %.2f\n  max pitch - %.2f\n  max ammunition - %i",
					m_name.c_str(),
					m_maxHitPoints,
					m_maxPower,
					m_maxReloadTime,
					m_turnSpeed,
					m_maxYaw,
					m_maxPitch,
					m_maxAmmunition);

				return str;
			}
	};
};

//------------------------------------------------------------------------------
