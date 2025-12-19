
//------------------------------------------------------------------------------
// PartDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class PartDesc {

		public:

			enum PartDescType {

				PDT_ARMOUR,
				PDT_BODY,
				PDT_ENGINE,
				PDT_PART,
				PDT_POWER_REACTOR,
				PDT_WEAPON

			};

			PartDescType	m_type;
			string			m_name;
			float			m_maxHitPoints;
			float			m_mass;
 
			__forceinline PartDesc(string name, float maxHitPoints)

				:	m_type(PDT_PART),
					m_name(name),
					m_maxHitPoints(maxHitPoints) { }

			__forceinline void* is(PartDescType type) { return (m_type == type) ? this : NULL; }
			__forceinline ArmourDesc* isArmourDesc() { return (ArmourDesc*)is(PDT_ARMOUR); }
			__forceinline BodyDesc* isBodyDesc() { return (BodyDesc*)is(PDT_BODY); }
			__forceinline EngineDesc* isEngineDesc() { return (EngineDesc*)is(PDT_ENGINE); }
			__forceinline PowerReactorDesc* isPowerReactorDesc() { return (PowerReactorDesc*)is(PDT_POWER_REACTOR); }
			__forceinline WeaponDesc* isWeaponDesc() { return (WeaponDesc*)is(PDT_WEAPON); }

			__forceinline virtual string toString(){

				char text[512];

				sprintf(
					text,
					"\
					Name                %s\n\
					Max Hit Points      %.2f",
					m_name.c_str(),
					m_maxHitPoints);

				return text;

			}

	};

};

//------------------------------------------------------------------------------
