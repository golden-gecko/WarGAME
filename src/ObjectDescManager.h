
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ResourceManager.h"

#include "ObjectDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectDescManager: public ResourceManager<ObjectDesc>, public Ogre::Singleton<ObjectDescManager> {

		public:

			typedef list<ObjectDesc*>::iterator Iterator;

			Iterator Begin() {

				return m_active.begin();
			}

			Iterator End() {

				return m_active.end();
			}

		public:

			ObjectDescManager() {

				ResourceManager::init(128);		
			}

			ObjectDesc* create(const string& name, ArmDesc* armDesc, ArmourDesc* armourDesc, BodyDesc* bodyDesc, EngineDesc* engineDesc, ExplosiveDesc* explosiveDesc, ReactorDesc* reactorDesc, ShieldDesc* shieldDesc, TeleporterDesc* teleporterDesc, WeaponDesc* weaponDesc) {

				ObjectDesc* objectDesc = ResourceManager::create(name);

				objectDesc->setArmDesc(armDesc);
				objectDesc->setArmourDesc(armourDesc);
				objectDesc->setBodyDesc(bodyDesc);
				objectDesc->setEngineDesc(engineDesc);
				objectDesc->setExplosiveDesc(explosiveDesc);
				objectDesc->setReactorDesc(reactorDesc);
				objectDesc->setShieldDesc(shieldDesc);
				objectDesc->setTeleporterDesc(teleporterDesc);
				objectDesc->setWeaponDesc(weaponDesc);

				return objectDesc;
			}

	};

};

//------------------------------------------------------------------------------
