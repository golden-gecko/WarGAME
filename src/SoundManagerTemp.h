
//------------------------------------------------------------------------------
// SoundManagerTemp.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "ResourceManagerTemp.h"
#include "Sound.h"

//------------------------------------------------------------------------------
// SoundManagerTemp
//------------------------------------------------------------------------------

namespace WarGAME {

	class SoundManagerTemp: public ResourceManagerTemp<SoundManagerTemp, Sound> {

		public:

			typedef list<Sound*>			List;
			typedef list<Sound*>::iterator	Iterator;

		public:

			virtual ~SoundManagerTemp();

			Sound* create(const char* soundName);

			bool init();

	};
};

//------------------------------------------------------------------------------
