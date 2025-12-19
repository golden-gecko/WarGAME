
//------------------------------------------------------------------------------
// Part.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "PartDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Part {

		public:

			enum PartType {

				PT_ARMOUR			= 0x01,
				PT_BODY				= 0x02,
				PT_ENERGY_SHIELD	= 0x04,
				PT_ENGINE			= 0x08,
				PT_EXPLOSIVE		= 0x10,
				PT_PART				= 0x20,
				PT_POWER_REACTOR	= 0x40,
				PT_WEAPON			= 0x80

			};

			enum PartState {

				PS_IDLE,
				PS_PROCCESSING_ORDER

			};

			ObjectTemp*		m_parent;
			PartDesc*	m_partDesc;
			float		m_hitPoints;
			PartType	m_type;
			PartState	m_state;
			float		m_timeSinceLastAiCheck;
			float		m_timeToNextAiCheck;
			string		m_name;

			Part(ObjectTemp* parent)
				:	m_parent(parent),
					m_name(""),
					m_type(PT_PART),
					m_state(PS_IDLE),
					m_partDesc(NULL),
					m_hitPoints(0.0f),
					m_timeSinceLastAiCheck(0.0f),
					m_timeToNextAiCheck(rand() % 1000 / 1000.0f) { }

			float getHitPoints() {

				return m_hitPoints;
			}

			float getMaxHitPoints() {

				if (m_partDesc)

					return m_partDesc->m_maxHitPoints;

				return 0.0f;
			}

			virtual void setDesc(PartDesc* partDesc) {

				m_partDesc = partDesc;
				m_hitPoints = getMaxHitPoints();
			}

			virtual string toString() {

				static char str[512];

				sprintf(
					str,
					"\
					  Name %s\n\
					  Hit Points %.0f/%.0f",
					m_name.c_str(),
					getHitPoints(), getMaxHitPoints());

				return str;
			}

			virtual bool update(float deltaTime) = 0;

	};
};

//------------------------------------------------------------------------------
