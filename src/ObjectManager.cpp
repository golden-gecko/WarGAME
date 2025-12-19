
//------------------------------------------------------------------------------
// ObjectManager.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "ObjectManager.h"

//------------------------------------------------------------------------------

ObjectManager::~ObjectManager(){

	deselectAll();
	destroyAll();

}

//------------------------------------------------------------------------------

void ObjectManager::add(Object* object){

	m_objects.push_back(object);

}

//------------------------------------------------------------------------------

void ObjectManager::deselect(Object* object){

	object->setSelected(false);

	m_selected.remove(object);

}

//------------------------------------------------------------------------------

void ObjectManager::deselectAll(){

	for (Iterator itr = m_selected.begin(); itr != m_selected.end(); itr++)

		(*itr)->setSelected(false);

	m_selected.clear();

}

//------------------------------------------------------------------------------

void ObjectManager::destroy(Object* object){

	m_objects.remove(object);

	delete object;

}

//------------------------------------------------------------------------------

void ObjectManager::destroyAll(){

	for (Iterator itr = m_objects.begin(); itr != m_objects.end(); itr++)

		delete *itr;

	m_objects.clear();

}

//------------------------------------------------------------------------------

int ObjectManager::getCount(){

	return (int)m_objects.size();

}

//------------------------------------------------------------------------------

ObjectManager::Iterator ObjectManager::getFirst(){

	return m_objects.begin();

}

//------------------------------------------------------------------------------

ObjectManager::Iterator ObjectManager::getLast(){

	return m_objects.end();

}

//------------------------------------------------------------------------------

void ObjectManager::select(Object* object){

	object->setSelected(true);

	m_selected.push_back(object);

}

//------------------------------------------------------------------------------

void ObjectManager::selecteAll(){

	for (Iterator itr = m_objects.begin(); itr != m_objects.end(); itr++)

		(*itr)->setSelected(true);

	m_selected = m_objects;

}

//------------------------------------------------------------------------------

void ObjectManager::update(float deltaTime){

	static List toRemove;

	for (Iterator itr = m_objects.begin(); itr != m_objects.end(); itr++)

		if ((*itr)->update(deltaTime) == false)

			toRemove.push_back(*itr);

	for (Iterator itr = toRemove.begin(); itr != toRemove.end(); itr++)

		destroy(*itr);

	toRemove.clear();

}

//------------------------------------------------------------------------------
