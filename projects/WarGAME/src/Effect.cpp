#include "Dependencies.h"

#include "Effect.h"
#include "Graphics.h"

Effect::Effect(const std::string& name, const std::string& script)
{
	mParticleSystem = Graphics::getSingleton().createParticleSystem(name, script);
	mParticleSystem->setRenderingDistance(256.0f);

	mSceneNode = Graphics::getSingleton().createSceneNode();
	mSceneNode->attachObject(mParticleSystem);

	setEnabled(false);
}
