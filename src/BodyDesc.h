

//------------------------------------------------------------------------------
// BodyDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "PartDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class BodyDesc : public PartDesc {

		public:

			string	m_meshName;
			bool	m_castShadows;

			BodyDesc(string name, float maxHitPoints, string meshName, bool castShadows)

				:	PartDesc(name, maxHitPoints),
					m_meshName(meshName),
					m_castShadows(castShadows)

			{

				m_type = PDT_BODY;

			}

			virtual string toString(){

				char text[512];

				sprintf(
					text,
					"\
					%s\n\
					Mesh Name           %s",
					PartDesc::toString().c_str(),
					m_meshName.c_str());

				return text;

			}

	};

};

//------------------------------------------------------------------------------
