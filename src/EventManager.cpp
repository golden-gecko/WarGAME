
//------------------------------------------------------------------------------
// EventManager.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "EventManager.h"
#include "Core.h"

//------------------------------------------------------------------------------

EventManager::EventManager(){

}

//------------------------------------------------------------------------------

EventManager::~EventManager(){

	removeAll();

}

//------------------------------------------------------------------------------

void EventManager::add(Event* Event){

	m_events.push_back(Event);

}

//------------------------------------------------------------------------------

void EventManager::remove(Event* Event){

	delete Event;

	m_events.remove(Event);

}

//------------------------------------------------------------------------------

void EventManager::removeAll(){

	for (Iterator itr = m_events.begin(); itr != m_events.end(); itr++)

		delete *itr;

	m_events.clear();

}

//------------------------------------------------------------------------------

void EventManager::update(float deltaTime){

	static List toRemove;

	for (Iterator itr = m_events.begin(); itr != m_events.end(); itr++)

		;

	for (Iterator itr = toRemove.begin(); itr != toRemove.end(); itr++)

		remove(*itr);

	toRemove.clear();

}

//------------------------------------------------------------------------------
