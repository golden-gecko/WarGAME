
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
			float	m_range;
			float	m_maxReloadTime;
			float	m_maxTurnSpeed;
			short	m_maxAmmunition;
			float	m_maxYaw;
			float	m_maxPitch;

			WeaponDesc(	string name,
						float maxHitPoints,
						string meshName,
						bool castShadows,
						float m_damage,
						float maxRange,
						float maxReloadTime,
						float maxTurnSpeed,
						short maxAmmunition)

				:	BodyDesc(name, maxHitPoints, meshName, castShadows),
					m_damage(m_damage),
					m_range(maxRange),
					m_maxReloadTime(maxReloadTime),
					m_maxTurnSpeed(maxTurnSpeed),
					m_maxAmmunition(maxAmmunition)
			{

				m_type = PDT_WEAPON;

			}

			virtual string toString(){

				char text[512];

				sprintf(
					text,
					"\
					%s\n\
					Max Damage          %.2f\n\
					Max Range           %.2f\n\
					Max ReloadTime      %.2f\n\
					Max TurnSpeed       %.2f\n\
					Max Ammunition      %i",
					PartDesc::toString().c_str(),
					m_damage,
					m_range,
					m_maxReloadTime,
					m_maxTurnSpeed,
					m_maxAmmunition);

				return text;

			}

	};

};

//------------------------------------------------------------------------------
