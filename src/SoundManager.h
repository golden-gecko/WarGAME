
//------------------------------------------------------------------------------
// SoundManager.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Sound.h"

//------------------------------------------------------------------------------
// SoundManager
//------------------------------------------------------------------------------

namespace WarGAME {

	class SoundManager : public Singleton<SoundManager> {

		public:

			typedef list<Sound*>			List;
			typedef list<Sound*>::iterator	Iterator;

		private:

			List m_sounds;

		public:

			~SoundManager();

			Sound* create(const char* soundName);

			void destroy(Sound* sound);

			void destroyAll();

			bool init();

	};

};

//------------------------------------------------------------------------------
