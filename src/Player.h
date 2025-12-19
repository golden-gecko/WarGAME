
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Resource.h"

//------------------------------------------------------------------------------
// Player
//------------------------------------------------------------------------------

namespace WarGAME {

	class Player: public Resource {

		protected:

			string	m_color;
			float	m_energyRatio;
			float	m_energyStored;
			float	m_maxEnergyStored;
			float	m_energyProduced;
			float	m_maxEnergyProduced;
			float	m_energyUsed;
			float	m_maxEnergyUsed;

		public:

			Player()

				:	m_color(""),
					m_energyRatio(1.0f),
					m_energyStored(0.0f),
					m_maxEnergyStored(0.0f),
					m_energyProduced(0.0f),
					m_maxEnergyProduced(0.0f),
					m_energyUsed(0.0f),
					m_maxEnergyUsed(0.0f) { }

			string getColor() {

				return m_color;
			}

			void setColor(const string& color) {

				m_color = color;
			}

			void increaseMaxEnergyStored(float maxEnergyStored) {

				m_maxEnergyStored += maxEnergyStored;
			}
			void increaseEnergyProduced(float energyProduced) {

				m_energyProduced += energyProduced;
			}
			void increaseMaxEnergyProduced(float maxEnergyProduced) {

				m_maxEnergyProduced += maxEnergyProduced;
			}

			void decreaseMaxEnergyStored(float maxEnergyStored) {

				m_maxEnergyStored -= maxEnergyStored;
			}
			void decreaseEnergyProduced(float energyProduced) {

				m_energyProduced -= energyProduced;
			}
			void decreaseMaxEnergyProduced(float maxEnergyProduced) {

				m_maxEnergyProduced -= maxEnergyProduced;
			}

			string toString();

			string toStringShort();

			string toStringEnemy();

			bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
