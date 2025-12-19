
//------------------------------------------------------------------------------
// SoundManager.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "SoundManager.h"

//------------------------------------------------------------------------------

SoundManager::~SoundManager() {

	fslShutDown();
}

//------------------------------------------------------------------------------

Sound* SoundManager::create(const char* soundName) {

	FSLsound* fslSound = fslLoadSound(soundName);

	if (fslSound) {

		Sound* sound = new Sound(soundName, fslSound);
			
		m_list.push_back(sound);

		return sound;
	}

	return NULL;
}

//------------------------------------------------------------------------------

bool SoundManager::init() {

	if (fslInitSpecify("DirectSound3D") == NULL)

		return false;

	fslInitEAX();

	fslSetListenerEnvironment(FSL_ENV_GENERIC);

	float listenerPosition[] = { 0.0f, 0.0f, 0.0f };

	fslSetListenerPositionA(listenerPosition);

	return true;
}

//------------------------------------------------------------------------------
