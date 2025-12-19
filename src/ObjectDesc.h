
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Resource.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectDesc: public Resource {

		protected:

			ArmDesc*		m_armDesc;
			ArmourDesc*		m_armourDesc;
			BodyDesc*		m_bodyDesc;
			EngineDesc*		m_engineDesc;
			ExplosiveDesc*	m_explosiveDesc;
			ReactorDesc*	m_reactorDesc;
			ShieldDesc*		m_shieldDesc;
			TeleporterDesc*	m_teleporterDesc;
			WeaponDesc*		m_weaponDesc;

		public:

			ObjectDesc()
				:	m_armDesc(NULL),
					m_armourDesc(NULL),
					m_bodyDesc(NULL),
					m_engineDesc(NULL),
					m_explosiveDesc(NULL),
					m_reactorDesc(NULL),
					m_shieldDesc(NULL),
					m_teleporterDesc(NULL),
					m_weaponDesc(NULL) { }

			ArmDesc* getArmDesc() {

				return m_armDesc;
			}
			ArmourDesc* getArmourDesc() {

				return m_armourDesc;
			}
			BodyDesc* getBodyDesc() {

				return m_bodyDesc;
			}
			EngineDesc* getEngineDesc() {

				return m_engineDesc;
			}
			ExplosiveDesc* getExplosiveDesc() {

				return m_explosiveDesc;
			}
			ReactorDesc* getReactorDesc() {

				return m_reactorDesc;
			}
			ShieldDesc* getShieldDesc() {

				return m_shieldDesc;
			}
			TeleporterDesc* getTeleporterDesc() {

				return m_teleporterDesc;
			}
			WeaponDesc* getWeaponDesc() {

				return m_weaponDesc;
			}
			float getEnergyCost();

			void setArmDesc(ArmDesc* armDesc) {

				m_armDesc = armDesc;
			}
			void setArmourDesc(ArmourDesc* armourDesc) {

				m_armourDesc = armourDesc;
			}
			void setBodyDesc(BodyDesc* bodyDesc) {

				m_bodyDesc = bodyDesc;
			}
			void setEngineDesc(EngineDesc* engineDesc) {

				m_engineDesc = engineDesc;
			}
			void setExplosiveDesc(ExplosiveDesc* explosiveDesc) {

				m_explosiveDesc = explosiveDesc;
			}
			void setReactorDesc(ReactorDesc* reactorDesc) {

				m_reactorDesc = reactorDesc;
			}
			void setShieldDesc(ShieldDesc* shieldDesc) {

				m_shieldDesc = shieldDesc;
			}
			void setTeleporterDesc(TeleporterDesc* teleporterDesc) {

				m_teleporterDesc = m_teleporterDesc;
			}
			void setWeaponDesc(WeaponDesc* weaponDesc) {

				m_weaponDesc = weaponDesc;
			}

			string toString() {

				return "object desc";
			}

	};

};

//------------------------------------------------------------------------------
