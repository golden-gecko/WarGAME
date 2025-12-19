
//------------------------------------------------------------------------------
// ObjectDesc.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "Object.h"

#include "ArmourDesc.h"
#include "BodyDesc.h"
#include "EngineDesc.h"
#include "WeaponDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectDesc {

		public:

			enum ObjectDescType {

				ODT_FORTIFICATION_DESC,
				ODT_OBJECT_DESC,
				ODT_VEHICLE_DESC

			};

			string			m_name;
			ObjectDescType	m_type;
			BodyDesc*		m_bodyDesc;

			ObjectDesc(string name, BodyDesc* bodyDesc)

				:	m_name(name),
					m_type(ODT_OBJECT_DESC),
					m_bodyDesc(bodyDesc)
			
			{
			
			}

			virtual string toString(){

				char text[512];

				sprintf(text, "");

				return text;

			}

	};

};

//------------------------------------------------------------------------------
