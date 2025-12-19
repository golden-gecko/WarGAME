
//------------------------------------------------------------------------------
// EventManager.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "EventManager.h"
#include "Core.h"

//------------------------------------------------------------------------------

void EventManager::update(float deltaTime) {

	static List toDestroy;

	for (Iterator itr = toDestroy.begin(); itr != toDestroy.end(); itr++)

		destroy(*itr);

	toDestroy.clear();

}

//------------------------------------------------------------------------------
