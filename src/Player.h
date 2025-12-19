
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
			float	m_armourDefenceModifier;
			float	m_armourHitPointsModifier;
			float	m_bodyHitPointsModifier;
			float	m_engineHitPointsModifier;
			float	m_engineSpeedModifier;
			float	m_weaponDamageModifier;
			float	m_weaponHitPointsModifier;
			float	m_weaponPowerModifier;
			float	m_weaponRangeModifier;
			float	m_weaponReloadTimeModifier;

		public:

			Player()

				:	m_color(""),
					m_energyRatio(1.0f),
					m_energyStored(0.0f),
					m_maxEnergyStored(0.0f),
					m_energyProduced(0.0f),
					m_maxEnergyProduced(0.0f),
					m_energyUsed(0.0f),
					m_maxEnergyUsed(0.0f),
					m_armourDefenceModifier(1.0f),
					m_armourHitPointsModifier(1.0f),
					m_bodyHitPointsModifier(1.0f),
					m_engineHitPointsModifier(1.0f),
					m_engineSpeedModifier(1.0f),
					m_weaponDamageModifier(1.0f),
					m_weaponHitPointsModifier(1.0f),
					m_weaponPowerModifier(1.0f),
					m_weaponRangeModifier(1.0f),
					m_weaponReloadTimeModifier(1.0f) { }

			string getColor() {

				return m_color;
			}

			void setColor(string color) {

				m_color = color;
			}

			string toString();

			string toStringShort();

			string toStringEnemy();

			bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
