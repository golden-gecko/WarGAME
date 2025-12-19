
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ResourceManager.h"

#include "Player.h"

//------------------------------------------------------------------------------
// PlayerManager
//------------------------------------------------------------------------------

namespace WarGAME {

	class PlayerManager: public ResourceManager<Player>, public Singleton<PlayerManager> {

		public:

			typedef list<Player*>::iterator Iterator;

			Iterator Begin() {

				return m_active.begin();
			}

			Iterator End() {

				return m_active.end();
			}

		public:

			PlayerManager(): ResourceManager(8) {

			}

			Player* create(string name, string color) {

				Player* player = ResourceManager::create(name);

				player->setColor(color);

				return player;
			}

			void update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
