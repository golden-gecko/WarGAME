
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Part.h"

#include "EngineDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Engine: public Part {

		protected:

			float			m_fuel;
			Ogre::Vector3	m_targetPos;
			Object*			m_targetObj;

		public:

			Engine(): Part(PT_ENGINE), m_fuel(0.0f), m_targetPos(Ogre::Vector3::ZERO), m_targetObj(NULL) { }

			EngineDesc* getEngineDesc() {

				return m_engineDesc;
			}
			float getFuel() {

				return m_fuel;
			}
			float getMaxFuel() {

				return m_engineDesc->getMaxFuel();
			}

			void setFuel(float fuel) {

				m_fuel = fuel;
			}
			void setPartDesc(PartDesc* partDesc);

			void follow(Object* targetObj) {

				m_targetObj	= targetObj;
				m_state		= PS_FOLLOW;
			}

			void move(const Ogre::Vector3& targetPos) {

				m_targetPos	= targetPos;
				m_state		= PS_MOVE_TO_POSITION;
			}

			void move(Object* targetObj) {

				m_targetObj	= targetObj;
				m_state		= PS_MOVE_TO_OBJECT;
			}

			void stop() {

				m_state = PS_NORMAL;
			}

			string toString();

			bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
