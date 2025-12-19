#include "Dependencies.h"
#include "Creature.h"
#include "Factory.h"
#include "Mine.h"
#include "ObjectManager.h"
#include "Plant.h"
#include "Resource.h"
#include "TemplateManager.h"
#include "Vehicle.h"

ObjectManager* Ogre::Singleton<ObjectManager>::ms_Singleton = NULL;

ObjectManager::ObjectManager() : mLastID(0)
{
}

Object* ObjectManager::create(const std::string& name, const Ogre::Vector3& position)
{
	if (ObjectTemplate* oTemplate = TemplateManager::getSingleton().get(name))
	{
		switch (oTemplate->type)
		{
			case OT_CREATURE:
			{
				CreatureTemplate* cTemplate = static_cast<CreatureTemplate*>(oTemplate);
				Creature* creature = new Creature(getNextID(), cTemplate->mesh);

				creature->setDamage(cTemplate->damage);
				creature->setDescription(cTemplate->description);
				creature->setEnergy(cTemplate->maxEnergy);
				creature->setEnergyRestore(cTemplate->energyRestore);
				creature->setHealth(cTemplate->maxHealth);
				creature->setHealthRestore(cTemplate->healthRestore);
				creature->setMaxEnergy(cTemplate->maxEnergy);
				creature->setMaxExperience(cTemplate->maxExperience);
				creature->setMaxHealth(cTemplate->maxHealth);
				creature->setMaxLevel(cTemplate->maxLevel);
				creature->setMaxSlope(cTemplate->maxSlope);
				creature->setMaxWaterDepth(cTemplate->maxWaterDepth);
				creature->setName(cTemplate->name);
				creature->setPosition(position);
				creature->setScale(cTemplate->scale);
				creature->setSightDistance(cTemplate->sightDistance);
				creature->setSpecies(cTemplate->species);
				creature->setSpeed(cTemplate->speed);

				mObjects.insert(std::make_pair(creature->getID(), creature));
				mTypes.insert(std::make_pair(creature->getType(), creature));

				return creature;
			}

			case OT_FACTORY:
			{
				FactoryTemplate* fTemplate = static_cast<FactoryTemplate*>(oTemplate);
				Factory* factory = new Factory(getNextID(), fTemplate->mesh);

				factory->setCost(fTemplate->cost);
				factory->setDescription(fTemplate->description);
				factory->setHealth(fTemplate->maxHealth);
				factory->setMaxHealth(fTemplate->maxHealth);
				factory->setMaxSlope(fTemplate->maxSlope);
				factory->setMaxWaterDepth(fTemplate->maxWaterDepth);
				factory->setName(fTemplate->name);
				factory->setPosition(position);
				factory->setScale(fTemplate->scale);
				factory->setSightDistance(fTemplate->sightDistance);
				factory->setUse(fTemplate->use);

				mObjects.insert(std::make_pair(factory->getID(), factory));
				mTypes.insert(std::make_pair(factory->getType(), factory));

				return factory;
			}

			case OT_PLANT:
			{
				PlantTemplate* pTemplate = static_cast<PlantTemplate*>(oTemplate);
				Plant* plant = new Plant(getNextID(), pTemplate->mesh);

				plant->setDescription(pTemplate->description);
				plant->setHealth(pTemplate->maxHealth);
				plant->setMaxHealth(pTemplate->maxHealth);
				plant->setMaxSlope(pTemplate->maxSlope);
				plant->setMaxWaterDepth(pTemplate->maxWaterDepth);
				plant->setName(pTemplate->name);
				plant->setPosition(position);
				plant->setScale(pTemplate->scale);
				plant->setSpecies(pTemplate->species);

				mObjects.insert(std::make_pair(plant->getID(), plant));
				mTypes.insert(std::make_pair(plant->getType(), plant));

				return plant;
			}

			case OT_RESOURCE:
			{
				ResourceTemplate* rTemplate = static_cast<ResourceTemplate*>(oTemplate);
				Resource* resource = new Resource(getNextID(), rTemplate->mesh);

				resource->setDescription(rTemplate->description);
				resource->setHealth(rTemplate->maxHealth);
				resource->setMaxHealth(rTemplate->maxHealth);
				resource->setMaxSlope(rTemplate->maxSlope);
				resource->setMaxWaterDepth(rTemplate->maxWaterDepth);
				resource->setName(rTemplate->name);
				resource->setPosition(position);
				resource->setScale(rTemplate->scale);

				mObjects.insert(std::make_pair(resource->getID(), resource));
				mTypes.insert(std::make_pair(resource->getType(), resource));

				return resource;
			}

			case OT_MINE:
			{
				MineTemplate* mTemplate = static_cast<MineTemplate*>(oTemplate);
				Mine* mine = new Mine(getNextID(), mTemplate->mesh);

				mine->setCost(mTemplate->cost);
				mine->setDescription(mTemplate->description);
				mine->setHealth(mTemplate->maxHealth);
				mine->setMaxHealth(mTemplate->maxHealth);
				mine->setMaxSlope(mTemplate->maxSlope);
				mine->setMaxWaterDepth(mTemplate->maxWaterDepth);
				mine->setName(mTemplate->name);
				mine->setPosition(position);
				mine->setProduce(mTemplate->produce);
				mine->setScale(mTemplate->scale);
				mine->setSightDistance(mTemplate->sightDistance);
				mine->setUse(mTemplate->use);

				mObjects.insert(std::make_pair(mine->getID(), mine));
				mTypes.insert(std::make_pair(mine->getType(), mine));

				return mine;
			}

			/*
			case OT_TURRET:
			{
				TurretTemplate* mTemplate = static_cast<TurretTemplate*>(oTemplate);
				Turret* turret = new Turret(getNextID(), mTemplate->mesh);

				turret->setCost(mTemplate->cost);
				turret->setDescription(mTemplate->description);
				turret->setHealth(mTemplate->maxHealth);
				turret->setMaxHealth(mTemplate->maxHealth);
				turret->setMaxSlope(mTemplate->maxSlope);
				turret->setMaxWaterDepth(mTemplate->maxWaterDepth);
				turret->setName(mTemplate->name);
				turret->setPosition(position);
				turret->setScale(mTemplate->scale);
				turret->setSightDistance(mTemplate->sightDistance);
				turret->setWeaponDamage(mTemplate->weaponDamage);
				turret->setWeaponDamageRadius(mTemplate->weaponDamageRadius);
				turret->setWeaponRange(mTemplate->weaponRange);
				turret->setWeaponRechargeTime(mTemplate->weaponRechargeTime);
				turret->setUse(mTemplate->use);

				mObjects.insert(std::make_pair(turret->getID(), turret));
				mTypes.insert(std::make_pair(turret->getType(), turret));

				return turret;
			}
			*/

			case OT_VEHICLE:
			{
				VehicleTemplate* vTemplate = static_cast<VehicleTemplate*>(oTemplate);
				Vehicle* vehicle = new Vehicle(getNextID(), vTemplate->mesh);

				vehicle->setCost(vTemplate->cost);
				vehicle->setDescription(vTemplate->description);
				vehicle->setHealth(vTemplate->maxHealth);
				vehicle->setMaxHealth(vTemplate->maxHealth);
				vehicle->setMaxSlope(vTemplate->maxSlope);
				vehicle->setMaxWaterDepth(vTemplate->maxWaterDepth);
				vehicle->setName(vTemplate->name);
				vehicle->setPosition(position);
				vehicle->setScale(vTemplate->scale);
				vehicle->setSightDistance(vTemplate->sightDistance);
				vehicle->setSpeed(vTemplate->speed);
				vehicle->setWeaponDamage(vTemplate->weaponDamage);
				vehicle->setWeaponDamageRadius(vTemplate->weaponDamageRadius);
				vehicle->setWeaponRange(vTemplate->weaponRange);
				vehicle->setWeaponRechargeTime(vTemplate->weaponRechargeTime);

				mObjects.insert(std::make_pair(vehicle->getID(), vehicle));
				mTypes.insert(std::make_pair(vehicle->getType(), vehicle));

				return vehicle;
			}
	
		}
	}

	return NULL;
}
