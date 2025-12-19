

//------------------------------------------------------------------------------
// BodyDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "PartDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {


			enum ArmourType {

				AT_NONE		= 0x00,
				AT_ALL		= 0x01

			};

			enum EngineType {

				ET_NONE		= 0x00,
				ET_AIR		= 0x01,
				ET_GROUND	= 0x02,
				ET_WATER	= 0x04,
				ET_ALL		= ET_AIR + ET_GROUND + ET_WATER

			};

			enum PowerReactorType {

				PRT_NONE	= 0x00,
				PRT_ALL		= 0x01

			};

			enum WeaponType {

				WT_NONE		= 0x00,
				WT_AIR		= 0x01,
				WT_WATER	= 0x02,
				WT_ALL		= WT_AIR + WT_WATER

			};

	class BodyDesc : public PartDesc {

		public:

			string				m_meshName;
			bool				m_castShadows;
			ArmourType			m_armourType;
			EngineType			m_engineType;
			PowerReactorType	m_powerReactorType;
			WeaponType			m_weaponType;

			BodyDesc(	string name,
						float maxHitPoints,
						string meshName,
						bool castShadows,
						ArmourType armourType,
						EngineType engineType,
						PowerReactorType powerReactorType,
						WeaponType weaponType)

				:	PartDesc(name, maxHitPoints),
					m_meshName(meshName),
					m_castShadows(castShadows),
					m_armourType(armourType),
					m_engineType(engineType),
					m_powerReactorType(powerReactorType),
					m_weaponType(weaponType)

			{
				m_type = PDT_BODY_DESC;
			}

			virtual string toString() {

				char str[512];

				sprintf(
					str,
					"\
					Body Desc\n\
					%s\n\
					  Mesh Name %s",
					PartDesc::toString().c_str(),
					m_meshName.c_str());

				return str;
			}

	};
};

//------------------------------------------------------------------------------
