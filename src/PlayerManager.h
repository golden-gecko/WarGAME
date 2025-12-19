
//------------------------------------------------------------------------------
// PlayerManager.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "Player.h"

//------------------------------------------------------------------------------
// PlayerManager
//------------------------------------------------------------------------------

namespace WarGAME {

	class PlayerManager : public Singleton <PlayerManager> {

		public:

			typedef list<Player*>			List;
			typedef list<Player*>::iterator	Iterator;

		private:

			List m_players;

		public:

			~PlayerManager();

			Player* add(Player* player);

			Player* get(string name);

			Iterator getFirst(){

				return m_players.begin();

			}

			Iterator getLast(){

				return m_players.end();

			}

			void remove(Player* player);

			void removeAll();

			void update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
