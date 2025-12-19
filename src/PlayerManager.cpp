
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PlayerManager.h"

//------------------------------------------------------------------------------

void PlayerManager::update(float deltaTime) {

	for (list<Player*>::iterator itr = m_active.begin(); itr != m_active.end(); itr++)

		(*itr)->update(deltaTime);
}

//------------------------------------------------------------------------------
