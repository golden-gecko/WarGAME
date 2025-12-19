
//------------------------------------------------------------------------------
// Vehicle.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "Engine.h"
#include "Fortification.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Vehicle : public Fortification {

		public:

			Engine* m_engine;

			Vehicle(	string armourName,
						string bodyName,
						string engineName,
						string weaponName,
						const Vector3& position);

			Vehicle(	ArmourDesc* amourDesc,
						BodyDesc* bodyDesc,
						EngineDesc* engineDesc,
						WeaponDesc* weaponDesc,
						const Vector3& position);

			virtual ~Vehicle(){

				delete m_engine;

			}

			virtual string toString();

			virtual bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
