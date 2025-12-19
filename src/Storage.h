
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Part.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Storage: public Part {

		protected:

			WORD	m_ammunition;
			float	m_energy;
			float	m_fuel;

		public:

			Storage()
				:	Part(PT_STORAGE),
					m_ammunition(0),
					m_energy(0.0f),
					m_fuel(0.0f) { }

			WORD getAmmunition() {

				return m_ammunition;
			}
			float getEnergy() {

				return m_energy;
			}
			float getFuel() {

				return m_fuel;
			}

			void setAmmunition(WORD ammunition) {

				m_ammunition = ammunition;
			}
			void setEnergy(float energy) {

				m_energy = energy;
			}
			void setFuel(float fuel) {

				m_fuel = fuel;
			}
			void setPartDesc(PartDesc* partDesc);

			string toString();

			bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
