
//------------------------------------------------------------------------------
// Vehicle.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Engine.h"
#include "Fortification.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Vehicle : public Fortification {

		public:

			Engine* m_engine;

			Vehicle();

			virtual ~Vehicle() {

				delete m_engine;

			}

			virtual string toString();

			virtual bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
