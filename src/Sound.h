
//------------------------------------------------------------------------------
// Sound.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

//------------------------------------------------------------------------------
// Sound
//------------------------------------------------------------------------------

namespace WarGAME {

	class Sound {

		protected:

			string		m_name;
			FSLsound*	m_sound;

		public:

			Sound(string name, FSLsound* fslSound);

			void play();

			void setLooping(bool looping);

			void setPosition(float x, float y, float z);

			void setPosition(const Vector3& position = Vector3::ZERO);

			void stop();

	};

};

//------------------------------------------------------------------------------
