
//------------------------------------------------------------------------------
// Building.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "Armour.h"
#include "Object.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Building : public Object {

		public:

			Armour* m_armour;

			Building(	string armourName,
						string bodyName,
						const Vector3& position);

			Building(	ArmourDesc* armourDesc,
						BodyDesc* bodyDesc,
						const Vector3& position);

			virtual ~Building(){

				delete m_armour;

			}

			virtual string toString();

	};

};

//------------------------------------------------------------------------------
