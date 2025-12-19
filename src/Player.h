
//------------------------------------------------------------------------------
// Player.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

//------------------------------------------------------------------------------
// Player
//------------------------------------------------------------------------------

namespace WarGAME {

	class Player {

		protected:

			string	m_name;

		public:

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

			Player(string name)
				
				:	m_name(name),
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
					m_weaponReloadTimeModifier(1.0f)

			{

			}

			string getName(){

				return m_name;

			}

			void setName(string name){

				m_name = name;

			}

			virtual string toString();

			virtual bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
