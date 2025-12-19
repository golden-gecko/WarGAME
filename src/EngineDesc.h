
//------------------------------------------------------------------------------
// EngineDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "PartDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class EngineDesc : public PartDesc {

		public:

			float m_maxFuel;
			float m_power;

			EngineDesc(	string name,
						float maxHitPoints,
						float maxFuel,
						float power)

				:	PartDesc(name, maxHitPoints),
					m_maxFuel(maxFuel),
					m_power(power)

			{

				m_type = PDT_ENGINE;

			}

			virtual string toString(){

				char text[512];

				sprintf(text, "");

				return text;

			}

	};

};

//------------------------------------------------------------------------------
