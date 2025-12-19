
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ResourceManager.h"

#include "Core.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Effect: public Resource {

		protected:

			Ogre::ParticleSystem*	m_particleSystem;
			Ogre::SceneNode*		m_sceneNode;

			Effect(const string& name)
				:	m_particleSystem(Core::getSingletonPtr()->createParticleSystem(name)),
					m_sceneNode(Core::getSingletonPtr()->createSceneNode())
			{
				m_sceneNode->attachObject(m_particleSystem);
			}

		public:

			void setColour(const Ogre::ColourValue& colour) {

				for (unsigned short i = 0; i < m_particleSystem->getNumEmitters(); i++)

					m_particleSystem->getEmitter(i)->setColour(colour);
			}
			void setDirection(const Ogre::Vector3& direction) {

				m_sceneNode->setDirection(direction, Ogre::Node::TS_WORLD);
			}
			void setEnabled(bool enabled) {

				for (unsigned short i = 0; i < m_particleSystem->getNumEmitters(); i++)

					m_particleSystem->getEmitter(i)->setEnabled(enabled);
			}
			void setPosition(const Ogre::Vector3& position) {

				m_sceneNode->setPosition(position);
			}
	};

	class Explosion: public Effect {

		public:

			Explosion(): Effect("explosion") { }
	};

	class Smoke: public Effect {

		public:

			Smoke(): Effect("smoke") { }
	};

	class Stream: public Effect {

		public:

			Stream(): Effect("stream") { }
	};

	class EffectManager: public Ogre::Singleton<EffectManager> {

		private:

			ResourceManager<Explosion>	m_explosion;
			ResourceManager<Smoke>		m_smoke;
			ResourceManager<Stream>		m_stream;

		public:

			void init() {

				m_explosion.init(256);
				m_smoke.init(256);
				m_stream.init(256);
			}

			Explosion* createExplosion(const string& name = "", const Ogre::ColourValue& colour = Ogre::ColourValue::White, bool enabled = true) {

				Explosion* explosion = m_explosion.create(name);

				explosion->setColour(colour);
				explosion->setEnabled(enabled);

				return explosion;
			}

			Smoke* createSmoke(const string& name = "", const Ogre::ColourValue& colour = Ogre::ColourValue::White, bool enabled = true) {

				Smoke* smoke = m_smoke.create(name);

				smoke->setColour(colour);
				smoke->setEnabled(enabled);

				return smoke;
			}

			Stream* createStream(const string& name = "", const Ogre::ColourValue& colour = Ogre::ColourValue::White, bool enabled = true) {

				Stream* stream = m_stream.create(name);

				stream->setColour(colour);
				stream->setEnabled(enabled);

				return stream;
			}

	};
};

//------------------------------------------------------------------------------
