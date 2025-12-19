
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartWithMesh.h"

#include "WeaponDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Weapon: public PartWithMesh {

		protected:

			float			m_reloadTime;
			WORD			m_ammunition;
			Object*			m_targetObj;
			Ogre::Vector3	m_targetPos;

		public:

			Weapon()

				:	PartWithMesh(PT_WEAPON), 
					m_reloadTime(0.0f),
					m_ammunition(0),
					m_targetObj(NULL),		
					m_targetPos(Ogre::Vector3(-1.0f)) { }

			WORD getAmmunition() {

				return m_ammunition;
			}
			WORD getMaxAmmunition() {

				return m_weaponDesc->getMaxAmmunition();
			}
			float getMaxReloadTime() {

				return m_weaponDesc->getMaxReloadTime();
			}
			float getReloadTime() {

				return m_reloadTime;
			}
			WeaponDesc* getWeaponDesc() {

				return m_weaponDesc;
			}

			void setPartDesc(PartDesc* partDesc);

			void attack(Object* targetObj) {

				m_targetObj = targetObj;

				m_targetPos = Ogre::Vector3(-1.0f);

				m_state = PS_PROCESSING_ORDER;
			}

			void attack(const Ogre::Vector3& targetPos) {

				m_targetPos = targetPos;

				m_targetObj = NULL;

				m_state = PS_PROCESSING_ORDER;
			}

			void stop() {
				
				m_state = PS_NORMAL;
			}

			void fire();

			string toString();

			bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
