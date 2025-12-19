
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ResourceManager.h"

#include "Arm.h"
#include "Armour.h"
#include "Body.h"
#include "Engine.h"
#include "Explosive.h"
#include "Object.h"
#include "Radar.h"
#include "Reactor.h"
#include "Shield.h"
#include "Teleporter.h"
#include "Weapon.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	namespace PartManager {

		class ArmManager: public ResourceManager<Arm>, public Ogre::Singleton<ArmManager> {

			public:

				typedef list<Arm*>			List;
				typedef list<Arm*>::iterator Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				ArmManager(): ResourceManager(1024) { }

				Arm* create(const string& name, ArmDesc* armDesc) {

					if (armDesc) {

						Arm* arm = ResourceManager::create(name);

						arm->setPartDesc(armDesc);

						return arm;
					}

					return NULL;
				}

				void destroy(Arm* arm) {

					arm->getParent()->setArm(NULL);				

					ResourceManager::destroy(arm);
				}

				void update(float deltaTime) {

					static List toDestroy;

					for (Iterator itr = Begin(); itr != End(); itr++)

						if ((*itr)->update(deltaTime) == false)

							toDestroy.push_back(*itr);

					for (Iterator itr = toDestroy.begin(); itr != toDestroy.end(); itr++)

						destroy(*itr);

					toDestroy.clear();
				}

		};

		class ArmourManager: public ResourceManager<Armour>, public Ogre::Singleton<ArmourManager> {

			public:

				typedef list<Armour*>			List;
				typedef list<Armour*>::iterator Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				ArmourManager(): ResourceManager(1024) { }

				Armour* create(const string& name, ArmourDesc* armourDesc) {

					if (armourDesc) {

						Armour* armour = ResourceManager::create(name);

						armour->setPartDesc(armourDesc);

						return armour;
					}

					return NULL;
				}

				void destroy(Armour* armour) {

					armour->getParent()->setArmour(NULL);				

					ResourceManager::destroy(armour);
				}

				void update(float deltaTime) {

					static List toDestroy;

					for (Iterator itr = Begin(); itr != End(); itr++)

						if ((*itr)->update(deltaTime) == false)

							toDestroy.push_back(*itr);

					for (Iterator itr = toDestroy.begin(); itr != toDestroy.end(); itr++)

						destroy(*itr);

					toDestroy.clear();
				}

		};

		class BodyManager: public ResourceManager<Body>, public Ogre::Singleton<BodyManager> {

			public:

				typedef list<Body*>				List;
				typedef list<Body*>::iterator	Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				BodyManager(): ResourceManager(1024) { }

				Body* create(const string& name, BodyDesc* bodyDesc) {

					if (bodyDesc) {

						Body* body = ResourceManager::create(name);

						body->setPartDesc(bodyDesc);

						return body;
					}

					return NULL;
				}

				void destroy(Body* body) {

					body->getParent()->setBody(NULL);				

					ResourceManager::destroy(body);
				}

				void update(float deltaTime) {

					static List toDestroy;

					for (Iterator itr = Begin(); itr != End(); itr++)

						if ((*itr)->update(deltaTime) == false)

							toDestroy.push_back(*itr);

					for (Iterator itr = toDestroy.begin(); itr != toDestroy.end(); itr++)

						destroy(*itr);

					toDestroy.clear();
				}

		};

		class EngineManager: public ResourceManager<Engine>, public Ogre::Singleton<EngineManager> {

			public:

				typedef list<Engine*>			List;
				typedef list<Engine*>::iterator Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				EngineManager(): ResourceManager(1024) { }

				Engine* create(const string& name, EngineDesc* engineDesc) {

					if (engineDesc) {

						Engine* engine = ResourceManager::create(name);

						engine->setPartDesc(engineDesc);

						return engine;
					}

					return NULL;
				}

				void destroy(Engine* engine) {

					engine->getParent()->setEngine(NULL);				

					ResourceManager::destroy(engine);
				}

				void update(float deltaTime) {

					static List toDestroy;

					for (Iterator itr = Begin(); itr != End(); itr++)

						if ((*itr)->update(deltaTime) == false)

							toDestroy.push_back(*itr);

					for (Iterator itr = toDestroy.begin(); itr != toDestroy.end(); itr++)

						destroy(*itr);

					toDestroy.clear();
				}

		};

		class ExplosiveManager: public ResourceManager<Explosive>, public Ogre::Singleton<ExplosiveManager> {

			public:

				typedef list<Explosive*>			List;
				typedef list<Explosive*>::iterator	Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				ExplosiveManager(): ResourceManager(1024) { }

				Explosive* create(const string& name, ExplosiveDesc* explosiveDesc) {

					if (explosiveDesc) {

						Explosive* explosive = ResourceManager::create(name);

						explosive->setPartDesc(explosiveDesc);

						return explosive;
					}

					return NULL;
				}

				void destroy(Explosive* explosive) {

					explosive->getParent()->setExplosive(NULL);				

					ResourceManager::destroy(explosive);
				}

				void update(float deltaTime) {

					static List toDestroy;

					for (Iterator itr = Begin(); itr != End(); itr++)

						if ((*itr)->update(deltaTime) == false)

							toDestroy.push_back(*itr);

					for (Iterator itr = toDestroy.begin(); itr != toDestroy.end(); itr++)

						destroy(*itr);

					toDestroy.clear();
				}

		};

		class ReactorManager: public ResourceManager<Reactor>, public Ogre::Singleton<ReactorManager> {

			public:

				typedef list<Reactor*>				List;
				typedef list<Reactor*>::iterator	Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				ReactorManager(): ResourceManager(1024) { }

				Reactor* create(const string& name, ReactorDesc* reactorDesc) {

					if (reactorDesc) {

						Reactor* reactor = ResourceManager::create(name);

						reactor->setPartDesc(reactorDesc);

						return reactor;
					}

					return NULL;
				}

				void destroy(Reactor* reactor) {

					reactor->getParent()->setShield(NULL);				

					ResourceManager::destroy(reactor);
				}

				void update(float deltaTime) {

					static List toDestroy;

					for (Iterator itr = Begin(); itr != End(); itr++)

						if ((*itr)->update(deltaTime) == false)

							toDestroy.push_back(*itr);

					for (Iterator itr = toDestroy.begin(); itr != toDestroy.end(); itr++)

						destroy(*itr);

					toDestroy.clear();
				}

		};

		class ShieldManager: public ResourceManager<Shield>, public Ogre::Singleton<ShieldManager> {

			public:

				typedef list<Shield*>			List;
				typedef list<Shield*>::iterator Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				ShieldManager(): ResourceManager(1024) { }

				Shield* create(const string& name, ShieldDesc* shieldDesc) {

					if (shieldDesc) {

						Shield* shield = ResourceManager::create(name);

						shield->setPartDesc(shieldDesc);

						return shield;
					}

					return NULL;
				}

				void destroy(Shield* shield) {

					shield->getParent()->setShield(NULL);				

					ResourceManager::destroy(shield);
				}

				void update(float deltaTime) {

					static List toDestroy;

					for (Iterator itr = Begin(); itr != End(); itr++)

						if ((*itr)->update(deltaTime) == false)

							toDestroy.push_back(*itr);

					for (Iterator itr = toDestroy.begin(); itr != toDestroy.end(); itr++)

						destroy(*itr);

					toDestroy.clear();
				}

		};

		class TeleporterManager: public ResourceManager<Teleporter>, public Ogre::Singleton<TeleporterManager> {

			public:

				typedef list<Teleporter*>			List;
				typedef list<Teleporter*>::iterator	Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				TeleporterManager(): ResourceManager(1024) { }

				Teleporter* create(const string& name, TeleporterDesc* teleporterDesc) {

					if (teleporterDesc) {

						Teleporter* teleporter = ResourceManager::create(name);

						teleporter->setPartDesc(teleporterDesc);

						return teleporter;
					}

					return NULL;
				}

				void destroy(Teleporter* teleporter) {

					teleporter->getParent()->setTeleporter(NULL);				

					ResourceManager::destroy(teleporter);
				}

				void update(float deltaTime) {

					static List toDestroy;

					for (Iterator itr = Begin(); itr != End(); itr++)

						if ((*itr)->update(deltaTime) == false)

							toDestroy.push_back(*itr);

					for (Iterator itr = toDestroy.begin(); itr != toDestroy.end(); itr++)

						destroy(*itr);

					toDestroy.clear();
				}

		};

		class WeaponManager: public ResourceManager<Weapon>, public Ogre::Singleton<WeaponManager> {

			public:

				typedef list<Weapon*>			List;
				typedef list<Weapon*>::iterator Iterator;

				Iterator Begin() {

					return m_active.begin();
				}

				Iterator End() {

					return m_active.end();
				}

			public:

				WeaponManager(): ResourceManager(1024) { }

				Weapon* create(const string& name, WeaponDesc* weaponDesc) {

					if (weaponDesc) {

						Weapon* weapon = ResourceManager::create(name);

						weapon->setPartDesc(weaponDesc);

						return weapon;
					}

					return NULL;
				}

				void destroy(Weapon* weapon) {

					weapon->getParent()->setWeapon(NULL);				

					ResourceManager::destroy(weapon);
				}

				void update(float deltaTime) {

					static List toDestroy;

					for (Iterator itr = Begin(); itr != End(); itr++)

						if ((*itr)->update(deltaTime) == false)

							toDestroy.push_back(*itr);

					for (Iterator itr = toDestroy.begin(); itr != toDestroy.end(); itr++)

						destroy(*itr);

					toDestroy.clear();
				}

		};

	};

};

//------------------------------------------------------------------------------
