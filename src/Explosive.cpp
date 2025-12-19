
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Explosive.h"
#include "ObjectManager.h"

//------------------------------------------------------------------------------

void Explosive::explode() {

	/*
	ObjectManager::List list;

	ObjectManager::getSingletonPtr()->getAllInRadius(list, m_parent->getPosition(), m_explosiveDesc->getRadius());

	for (ObjectManager::Iterator itr = list.begin(); itr != list.end(); itr++)

		(*itr)->damage(m_explosiveDesc->getDamage() * ((*itr)->getPosition() - m_parent->getPosition()).length() / m_explosiveDesc->getRadius());
	*/
}

//------------------------------------------------------------------------------

string Explosive::toString() {

	return "Explosive";
}

//------------------------------------------------------------------------------

bool Explosive::update(float deltaTime) {

	return Part::update(deltaTime);
}

//------------------------------------------------------------------------------
