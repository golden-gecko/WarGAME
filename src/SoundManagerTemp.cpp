
//------------------------------------------------------------------------------
// SoundManagerTemp.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "SoundManagerTemp.h"

//------------------------------------------------------------------------------

SoundManagerTemp::~SoundManagerTemp() {

	fslShutDown();
}

//------------------------------------------------------------------------------

Sound* SoundManagerTemp::create(const char* soundName) {

	FSLsound* fslSound = fslLoadSound(soundName);

	if (fslSound) {

		Sound* sound = new Sound(soundName, fslSound);
			
		m_list.push_back(sound);

		return sound;
	}

	return NULL;
}

//------------------------------------------------------------------------------

bool SoundManagerTemp::init() {

	if (fslInitSpecify("DirectSound3D") == NULL)

		return false;

	fslInitEAX();

	fslSetListenerEnvironment(FSL_ENV_GENERIC);

	float listenerPosition[] = { 0.0f, 0.0f, 0.0f };

	fslSetListenerPositionA(listenerPosition);

	return true;
}

//------------------------------------------------------------------------------
