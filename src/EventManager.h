
//------------------------------------------------------------------------------
// EventManager.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"
#include "Event.h"
#include "ResourceManagerTemp.h"

//------------------------------------------------------------------------------
// EventManager
//------------------------------------------------------------------------------

namespace WarGAME
{
	class EventManager: public ResourceManagerTemp<EventManager, Event>
	{
		public:

			typedef list<Event*>			List;
			typedef list<Event*>::iterator	Iterator;

		public:

			void update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
