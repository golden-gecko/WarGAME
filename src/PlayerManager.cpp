
//------------------------------------------------------------------------------
// PlayerManager.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "PlayerManager.h"

//------------------------------------------------------------------------------

PlayerManager::~PlayerManager(){

	removeAll();

}

//------------------------------------------------------------------------------

Player* PlayerManager::add(Player* player){

	m_players.push_back(player);

	return player;

}

//------------------------------------------------------------------------------

Player* PlayerManager::get(string name){

	for (Iterator i = m_players.begin(); i != m_players.end(); i++)

		if ((*i)->getName() == name)

			return (*i);

	return NULL;

}

//------------------------------------------------------------------------------

void PlayerManager::remove(Player* player){

	m_players.remove(player);

	delete player;

}

//------------------------------------------------------------------------------

void PlayerManager::removeAll(){

	for (Iterator i = m_players.begin(); i != m_players.end(); i++)

		delete (*i);

}

//------------------------------------------------------------------------------

void PlayerManager::update(float deltaTime){

	static List toRemove;

	for (Iterator itr = m_players.begin(); itr != m_players.end(); itr++)

		if ((*itr)->update(deltaTime) == false)

			toRemove.push_back(*itr);

	for (Iterator itr = toRemove.begin(); itr != toRemove.end(); itr++)

		remove(*itr);

	toRemove.clear();

}

//------------------------------------------------------------------------------
