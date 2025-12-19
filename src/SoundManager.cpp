
//------------------------------------------------------------------------------
// SoundManager.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "SoundManager.h"

//------------------------------------------------------------------------------

SoundManager::~SoundManager(){

	destroyAll();

	fslShutDown();

}

//------------------------------------------------------------------------------

Sound* SoundManager::create(const char* soundName){

	FSLsound* fslSound = fslLoadSound(soundName);

	if (fslSound) {

		Sound* sound = new Sound(soundName, fslSound);
			
		m_sounds.push_back(sound);

		return sound;

	}

	return NULL;

}

//------------------------------------------------------------------------------

void SoundManager::destroy(Sound* sound){

	m_sounds.remove(sound);

	delete sound;

}

//------------------------------------------------------------------------------

void SoundManager::destroyAll(){

	for (Iterator itr = m_sounds.begin(); itr != m_sounds.end(); itr++)

		delete (*itr);

	m_sounds.clear();

}

//------------------------------------------------------------------------------

bool SoundManager::init(){

	if (fslInitSpecify("DirectSound3D") == NULL)

		return false;

	fslInitEAX();

	fslSetListenerEnvironment(FSL_ENV_GENERIC);

	float listenerPosition[] = { 0.0f, 0.0f, 0.0f };

	fslSetListenerPositionA(listenerPosition);

	return true;

}

//------------------------------------------------------------------------------
