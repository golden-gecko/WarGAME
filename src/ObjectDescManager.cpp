
//------------------------------------------------------------------------------
// ObjectDescManager.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "ObjectDescManager.h"

//------------------------------------------------------------------------------

ObjectDescManager::~ObjectDescManager(){

	destroyAll();

}

//------------------------------------------------------------------------------

void ObjectDescManager::add(ObjectDesc* objectDesc){

	m_objectDescs.push_back(objectDesc);

}

//------------------------------------------------------------------------------

void ObjectDescManager::destroy(ObjectDesc* objectDesc){

	m_objectDescs.remove(objectDesc);

	delete objectDesc;

}

//------------------------------------------------------------------------------

void ObjectDescManager::destroyAll(){

	for (Iterator itr = m_objectDescs.begin(); itr != m_objectDescs.end(); itr++)

		delete *itr;

	m_objectDescs.clear();

}

//------------------------------------------------------------------------------

int ObjectDescManager::getCount(){

	return (int)m_objectDescs.size();

}

//------------------------------------------------------------------------------

ObjectDescManager::Iterator ObjectDescManager::getFirst(){

	return m_objectDescs.begin();

}

//------------------------------------------------------------------------------

ObjectDescManager::Iterator ObjectDescManager::getLast(){

	return m_objectDescs.end();

}

//------------------------------------------------------------------------------
