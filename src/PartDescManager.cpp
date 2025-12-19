
//------------------------------------------------------------------------------
// PartDescManager.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "PartDescManager.h"

//------------------------------------------------------------------------------

PartDescManager::~PartDescManager(){

	destroyAll();

}

//------------------------------------------------------------------------------

void PartDescManager::add(PartDesc* descriptor){

	m_modules.push_back(descriptor);

}

//------------------------------------------------------------------------------

void PartDescManager::destroy(PartDesc* descriptor){

	m_modules.remove(descriptor);

	delete descriptor;

}

//------------------------------------------------------------------------------

void PartDescManager::destroyAll(){

	for (Iterator itr = m_modules.begin(); itr != m_modules.end(); itr++)

		delete *itr;

	m_modules.clear();

}

//------------------------------------------------------------------------------

PartDesc* PartDescManager::getByName(string name){

	for (Iterator itr = m_modules.begin(); itr != m_modules.end(); itr++)

		if ((*itr)->m_name == name)

			return (*itr);

	return NULL;

}

//------------------------------------------------------------------------------

int PartDescManager::getCount(){

	return (int)m_modules.size();

}

//------------------------------------------------------------------------------

PartDescManager::Iterator PartDescManager::getFirst(){

	return m_modules.begin();

}

//------------------------------------------------------------------------------

PartDescManager::Iterator PartDescManager::getLast(){

	return m_modules.end();

}

//------------------------------------------------------------------------------
