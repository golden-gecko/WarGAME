
//------------------------------------------------------------------------------
// PowerPlant.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Building.h"
#include "PowerReactor.h"
#include "PowerReactorDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class PowerPlant : public Building {

		public:

			PowerReactor* m_powerReactor;

			PowerPlant(	string armourName,
						string bodyName,
						string powerReactorName,
						const Vector3& position);

			PowerPlant(	ArmourDesc* armourDesc,
						BodyDesc* bodyDesc,
						PowerReactorDesc* powerReactorDesc,
						const Vector3& position);

			virtual ~PowerPlant(){

				delete m_powerReactor;

			}

			virtual void setPlayer(Player* player = NULL){

				if (m_player) {

					m_player->m_maxEnergyStored -= m_powerReactor->m_powerReactorDesc->m_maxEnergyStored;
					m_player->m_energyProduced -= m_powerReactor->m_powerReactorDesc->m_maxEnergyProduced;
					m_player->m_maxEnergyProduced -= m_powerReactor->m_powerReactorDesc->m_maxEnergyProduced;

				}

				Object::setPlayer(player);

				if (m_player) {

					m_player->m_maxEnergyStored += m_powerReactor->m_powerReactorDesc->m_maxEnergyStored;
					m_player->m_energyProduced += m_powerReactor->m_powerReactorDesc->m_maxEnergyProduced;
					m_player->m_maxEnergyProduced += m_powerReactor->m_powerReactorDesc->m_maxEnergyProduced;

				}
					
			}

	};

};

//------------------------------------------------------------------------------
