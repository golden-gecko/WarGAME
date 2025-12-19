
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Resource.h"

#include "ObjectOrder.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Unit: public Resource {

		protected:

			Arm*	m_arm;
			Armour*	m_armour;
			Engine*	m_engine;
			Radar*	m_radar;
			Shield*	m_shield;
			Weapon*	m_weapon;

		public:

			Unit():	m_arm(NULL),
					m_armour(NULL),
					m_engine(NULL),
					m_shield(NULL),
					m_radar(NULL),
					m_weapon(NULL) { }

			Armour* getArmour() {

				return m_armour;
			}
			Engine* getEngine() {

				return m_engine;
			}
			Shield* getShield() {

				return m_shield;
			}
			Weapon* getWeapon() {

				return m_weapon;
			}

			void setArmour(Armour* armour);
			void setEngine(Engine* engine);
			void setShield(Shield* shield);
			void setWeapon(Weapon* weapon);

			string toString();

			bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
