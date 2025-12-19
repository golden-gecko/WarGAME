
//------------------------------------------------------------------------------
// ObjectDescManager.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "ObjectDescManager.h"

//------------------------------------------------------------------------------

void ObjectDescManager::add(ObjectDesc* objectDesc) {

	m_list.push_back(objectDesc);

}

//------------------------------------------------------------------------------

ObjectDesc* ObjectDescManager::getByName(string name) {

	for (Iterator itr = m_list.begin(); itr != m_list.end(); itr++)

		if ((*itr)->m_name == name)

			return (*itr);

	return NULL;

}

//------------------------------------------------------------------------------

ObjectDescManager::Iterator ObjectDescManager::getFirst() {

	return m_list.begin();

}

//------------------------------------------------------------------------------

ObjectDescManager::Iterator ObjectDescManager::getLast() {

	return m_list.end();

}

//------------------------------------------------------------------------------
