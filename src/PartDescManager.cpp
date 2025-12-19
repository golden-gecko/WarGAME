
//------------------------------------------------------------------------------
// PartDescManager.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "PartDescManager.h"

//------------------------------------------------------------------------------

void PartDescManager::add(PartDesc* descriptor) {

	m_list.push_back(descriptor);

}

//------------------------------------------------------------------------------

PartDesc* PartDescManager::getByName(string name) {

	for (Iterator itr = m_list.begin(); itr != m_list.end(); itr++)

		if ((*itr)->m_name == name)

			return (*itr);

	return NULL;

}

//------------------------------------------------------------------------------

PartDescManager::Iterator PartDescManager::getFirst() {

	return m_list.begin();

}

//------------------------------------------------------------------------------

PartDescManager::Iterator PartDescManager::getLast() {

	return m_list.end();

}

//------------------------------------------------------------------------------
