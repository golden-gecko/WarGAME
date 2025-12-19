
//------------------------------------------------------------------------------
// WeaponDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "BodyDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class WeaponDesc : public BodyDesc {

		public:

			float	m_damage;
			float	m_maxRange;
			float	m_maxReloadTime;
			float	m_maxTurnSpeed;
			short	m_maxAmmunition;
			float	m_maxYaw;
			float	m_maxPitch;

			WeaponDesc(	string name,
						float maxHitPoints,
						string meshName,
						bool castShadows,
						float damage,
						float maxRange,
						float maxReloadTime,
						float maxTurnSpeed,
						short maxAmmunition)

				:	BodyDesc(name, maxHitPoints, meshName, castShadows, AT_NONE, ET_NONE, PRT_NONE, WT_NONE),
					m_damage(damage),
					m_maxRange(maxRange),
					m_maxReloadTime(maxReloadTime),
					m_maxTurnSpeed(maxTurnSpeed),
					m_maxAmmunition(maxAmmunition)
			{
				m_type = PDT_WEAPON_DESC;
			}

			virtual string toString() {

				static char str[512];

				sprintf(
					str,
					"\
					Weapon Desc\n\
					%s\n\
					  Damage %.2f\n\
					  Max Range %.2f\n\
					  Max ReloadTime %.2f\n\
					  Max TurnSpeed %.2f\n\
					  Max Ammunition %i",
					PartDesc::toString().c_str(),
					m_damage,
					m_maxRange,
					m_maxReloadTime,
					m_maxTurnSpeed,
					m_maxAmmunition);

				return str;
			}

	};
};

//------------------------------------------------------------------------------
