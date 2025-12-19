
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

	class PlayerManager: public ResourceManager<Player>, public Ogre::Singleton<PlayerManager> {

		public:

			typedef list<Player*>			List;
			typedef list<Player*>::iterator	Iterator;

			Iterator Begin() {

				return m_active.begin();
			}

			Iterator End() {

				return m_active.end();
			}

		public:

			PlayerManager(): ResourceManager(8) { }

			Player* create(const string& name, const string& color) {

				Player* player = ResourceManager::create(name);

				player->setColor(color);

				return player;
			}

			void update(float deltaTime) {

				for (list<Player*>::iterator itr = m_active.begin(); itr != m_active.end(); itr++)

					(*itr)->update(deltaTime);
			}

	};

};

//------------------------------------------------------------------------------
