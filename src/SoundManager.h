
//------------------------------------------------------------------------------
// SoundManager.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "ResourceManagerTemp.h"
#include "Sound.h"

//------------------------------------------------------------------------------
// SoundManager
//------------------------------------------------------------------------------

namespace WarGAME {

	class SoundManager: public ResourceManagerTemp<SoundManager, Sound> {

		public:

			typedef list<Sound*>			List;
			typedef list<Sound*>::iterator	Iterator;

		public:

			virtual ~SoundManager();

			Sound* create(const char* soundName);

			bool init();

	};
};

//------------------------------------------------------------------------------
