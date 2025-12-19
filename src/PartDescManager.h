
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ResourceManager.h"

#include "ArmDesc.h"
#include "ArmourDesc.h"
#include "BodyDesc.h"
#include "EngineDesc.h"
#include "ExplosiveDesc.h"
#include "ReactorDesc.h"
#include "ShieldDesc.h"
#include "TeleporterDesc.h"
#include "WeaponDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	namespace PartDescManager {

//------------------------------------------------------------------------------

		class ArmDescManager: public ResourceManager<ArmDesc>, public Ogre::Singleton<ArmDescManager> {

			public:

				typedef list<ArmDesc*>::iterator Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				ArmDescManager() {

					ResourceManager::init(32);
				}

				ArmDesc* create(const string& name, float maxHitPoints, const string& meshName, float maxEnergyUsed) {

					ArmDesc* armDesc = ResourceManager::create(name);

					armDesc->setMaxHitPoints(maxHitPoints);
					armDesc->setMeshName(meshName);
					armDesc->setMaxEnergyUsed(maxEnergyUsed);

					return armDesc;
				}

		};

//------------------------------------------------------------------------------

		class ArmourDescManager: public ResourceManager<ArmourDesc>, public Ogre::Singleton<ArmourDescManager> {

			public:

				typedef list<ArmourDesc*>::iterator Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				ArmourDescManager() {
					
					ResourceManager::init(32);
				}

				ArmourDesc* create(const string& name, float maxHitPoints, float defence) {

					ArmourDesc* armourDesc = ResourceManager::create(name);

					armourDesc->setMaxHitPoints(maxHitPoints);
					armourDesc->setDefense(defence);

					return armourDesc;
				}

		};

//------------------------------------------------------------------------------

		class BodyDescManager: public ResourceManager<BodyDesc>, public Ogre::Singleton<BodyDescManager> {

			public:

				typedef list<BodyDesc*>::iterator Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				BodyDescManager() {
					
					ResourceManager::init(32);
				}

				BodyDesc* create(const string& name, float maxHitPoints, const string& meshName) {

					BodyDesc* bodyDesc = ResourceManager::create(name);

					bodyDesc->setMaxHitPoints(maxHitPoints);
					bodyDesc->setMeshName(meshName);

					return bodyDesc;
				}

		};

//------------------------------------------------------------------------------

		class EngineDescManager: public ResourceManager<EngineDesc>, public Ogre::Singleton<EngineDescManager> {

			public:

				typedef list<EngineDesc*>::iterator Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				EngineDescManager() {

					ResourceManager::init(32);
				}

				EngineDesc* create(const string& name, float maxHitPoints, float maxPower, float maxFuel) {

					EngineDesc* engineDesc = ResourceManager::create(name);

					engineDesc->setMaxHitPoints(maxHitPoints);
					engineDesc->setMaxPower(maxPower);
					engineDesc->setMaxFuel(maxFuel);

					return engineDesc;
				}

		};

//------------------------------------------------------------------------------

		class ExplosiveDescManager: public ResourceManager<ExplosiveDesc>, public Ogre::Singleton<ExplosiveDescManager> {

			public:

				typedef list<ExplosiveDesc*>::iterator Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				ExplosiveDescManager() {
					
					ResourceManager::init(32);
				}

				ExplosiveDesc* create(const string& name, float maxHitPoints, float damage, float radius) {

					ExplosiveDesc* explosiveDesc = ResourceManager::create(name);

					explosiveDesc->setMaxHitPoints(maxHitPoints);
					explosiveDesc->setDamage(damage);
					explosiveDesc->setRadius(radius);

					return explosiveDesc;
				}

		};

//------------------------------------------------------------------------------

		class ReactorDescManager: public ResourceManager<ReactorDesc>, public Ogre::Singleton<ReactorDescManager> {

			public:

				typedef list<ReactorDesc*>::iterator Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				ReactorDescManager() {

					ResourceManager::init(32);
				}

				ReactorDesc* create(const string& name, float maxHitPoints, float maxEnergyStored, float maxEnergyProduced) {

					ReactorDesc* reactorDesc = ResourceManager::create(name);

					reactorDesc->setMaxHitPoints(maxHitPoints);
					reactorDesc->setMaxEnergyStored(maxEnergyStored);
					reactorDesc->setMaxEnergyProduced(maxEnergyProduced);

					return reactorDesc;
				}

		};

//------------------------------------------------------------------------------

		class ShieldDescManager: public ResourceManager<ShieldDesc>, public Ogre::Singleton<ShieldDescManager> {

			public:

				typedef list<ShieldDesc*>::iterator Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				ShieldDescManager() {

					ResourceManager::init(32);
				}

				ShieldDesc* create(const string& name, float maxHitPoints, const string& meshName, float regenerationRate) {

					ShieldDesc* shieldDesc = ResourceManager::create(name);

					shieldDesc->setMaxHitPoints(maxHitPoints);
					shieldDesc->setMeshName(meshName);
					shieldDesc->setRegenerationRate(regenerationRate);

					return shieldDesc;
				}

		};

//------------------------------------------------------------------------------

		class TeleporterDescManager: public ResourceManager<TeleporterDesc>, public Ogre::Singleton<TeleporterDescManager> {

			public:

				typedef list<TeleporterDesc*>::iterator Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				TeleporterDescManager() {

					ResourceManager::init(32);
				}

				TeleporterDesc* create(const string& name, float maxHitPoints, const string& meshName) {

					TeleporterDesc* teleporterDesc = ResourceManager::create(name);

					teleporterDesc->setMaxHitPoints(maxHitPoints);
					teleporterDesc->setMeshName(meshName);

					return teleporterDesc;
				}

		};

//------------------------------------------------------------------------------

		class WeaponDescManager: public ResourceManager<WeaponDesc>, public Ogre::Singleton<WeaponDescManager> {

			public:

				typedef list<WeaponDesc*>::iterator Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				WeaponDescManager() {

					ResourceManager::init(32);
				}

				WeaponDesc* create(const string& name, float maxHitPoints, const string& meshName, float maxReloadTime, float turnSpeed, float maxYaw, float maxPitch, float maxPower, float maxAmmunition) {

					WeaponDesc* weaponDesc = ResourceManager::create(name);

					weaponDesc->setMaxHitPoints(maxHitPoints);
					weaponDesc->setMeshName(meshName);
					weaponDesc->setMaxPower(maxPower);
					weaponDesc->setMaxReloadTime(maxReloadTime);
					weaponDesc->setTurnSpeed(turnSpeed);
					weaponDesc->setMaxYaw(maxYaw);
					weaponDesc->setMaxPitch(maxPitch);
					weaponDesc->setMaxAmmunition(maxAmmunition);

					return weaponDesc;
				}

		};

	};

};

//------------------------------------------------------------------------------
