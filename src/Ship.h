
//------------------------------------------------------------------------------
// Ship.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "ObjectTemp.h"

#include "Armour.h"
#include "Body.h"
#include "Engine.h"
#include "Weapon.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Ship: public ObjectTemp {

		public:

			Armour*	m_armour;
//			Body*	m_body;
			Engine*	m_engine;
			Weapon*	m_weapon;

			Ship(): ObjectTemp() {

				m_armour = new Armour(this);
//				m_body = new new Body(this);
				m_engine = new Engine(this);
				m_weapon = new Weapon(this);
			}

	};
};

//------------------------------------------------------------------------------
