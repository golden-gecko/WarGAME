
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Resource.h"
#include "ResourceManager.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Effect: public Resource {

		protected:

			Ogre::ParticleSystem*	m_particleSystem;
			Ogre::SceneNode*		m_sceneNode;

		public:

			Effect(): m_particleSystem(NULL), m_sceneNode(NULL) { }

			void create(const string& name);
			void destroy();

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

				if (enabled && m_particleSystem->isAttached() == false)

					m_sceneNode->attachObject(m_particleSystem);
			}
			void setPosition(const Ogre::Vector3& position) {

				m_sceneNode->setPosition(position);
			}
			void setPosition(float x, float y, float z) {

				m_sceneNode->setPosition(x, y, z);
			}

			void update(float deltaTime) {

				if (m_particleSystem->getNumParticles() == 0)

					m_sceneNode->detachObject(m_particleSystem);
			}
	};

	class Explosion: public Effect {

	};

	class Smoke: public Effect {

	};

	class Stream: public Effect {

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

				for (int i = 0; i < 256; i++) {

					m_explosion[i].create("explosion");
					m_smoke[i].create("smoke");
					m_stream[i].create("stream");
				}
			}

			Explosion* createExplosion(const string& name = "") {

				Explosion* explosion = m_explosion.create(name);

				return explosion;
			}

			Smoke* createSmoke(const string& name = "") {

				Smoke* smoke = m_smoke.create(name);

				return smoke;
			}

			Stream* createStream(const string& name = "") {

				Stream* stream = m_stream.create(name);

				return stream;
			}

			void destroyExplosion(Explosion* explosion) {

				m_explosion.destroy(explosion);
			}

			void destroySmoke(Smoke* smoke) {
				
				m_smoke.destroy(smoke);
			}

			void destroyStream(Stream* stream) {

				m_stream.destroy(stream);
			}

			void setSpeed(float speed) {

			}
	};
};

//------------------------------------------------------------------------------
