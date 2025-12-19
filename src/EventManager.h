
//------------------------------------------------------------------------------
// EventManager.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "Event.h"

//------------------------------------------------------------------------------
// EventManager
//------------------------------------------------------------------------------

namespace WarGAME {

	class EventManager : public Singleton<EventManager> {
		
		public:

			typedef list<Event*>			List;
			typedef list<Event*>::iterator	Iterator;

		private:

			List m_events;

		public:

			EventManager();

			~EventManager();

			void add(Event* Event);

			void remove(Event* Event);

			void removeAll();

			void update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
