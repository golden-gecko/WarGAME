
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ObjectManager.h"

#include "PartManager.h"

//------------------------------------------------------------------------------

Building* ObjectManager::createBuilding(BuildingDesc* buildingDesc, const string& name) {

	Building* building = m_building.create(name);

	return building;
}

//------------------------------------------------------------------------------

Object* ObjectManager::createObject(ObjectDesc* objectDesc, const string& name) {

	Object* object = m_object.create(name);

	object->create();

	object->setArm(
		PartManager::ArmManager::getSingletonPtr()->create(
			"arm",
			objectDesc->getArmDesc()
		)
	);

	object->setArmour(
		PartManager::ArmourManager::getSingletonPtr()->create(
			"armour",
			objectDesc->getArmourDesc()
		)
	);

	object->setBody(
		PartManager::BodyManager::getSingletonPtr()->create(
			"body",
			objectDesc->getBodyDesc()
		)
	);

	object->setEngine(
		PartManager::EngineManager::getSingletonPtr()->create(
			"engine",
			objectDesc->getEngineDesc()
		)
	);

	object->setExplosive(
		PartManager::ExplosiveManager::getSingletonPtr()->create(
			"explosive",
			objectDesc->getExplosiveDesc()
		)
	);

	object->setReactor(
		PartManager::ReactorManager::getSingletonPtr()->create(
			"reactor",
			objectDesc->getReactorDesc()
		)
	);

	object->setShield(
		PartManager::ShieldManager::getSingletonPtr()->create(
			"shield",
			objectDesc->getShieldDesc()
		)
	);

	object->setTeleporter(
		PartManager::TeleporterManager::getSingletonPtr()->create(
			"teleporter",
			objectDesc->getTeleporterDesc()
		)
	);

	object->setWeapon(
		PartManager::WeaponManager::getSingletonPtr()->create(
			"weapon",
			objectDesc->getWeaponDesc()
		)
	);

	return object;
}

//------------------------------------------------------------------------------

Projectile* ObjectManager::createProjectile(ProjectileDesc* projectileDesc, const string& name) {

	Projectile* projectile = m_projectile.create(name);

	return projectile;
}

//------------------------------------------------------------------------------

Unit* ObjectManager::createUnit(UnitDesc* unitDesc, const string& name) {

	Unit* unit = m_unit.create(name);

	return unit;
}

//------------------------------------------------------------------------------

void ObjectManager::destroyObject(Object* object) {

	object->destroy();

	m_object.destroy(object);
}

//------------------------------------------------------------------------------

void ObjectManager::getAllInRadius(List& list, Ogre::Vector3 point, float radius) {

	/*
	for (Iterator itr = m_active.begin(); itr != m_active.end(); itr++)

		if (((*itr)->getPosition() - point).length() <= radius)

			list.push_back(*itr);
	//*/
}

//------------------------------------------------------------------------------

Object* ObjectManager::getNearest(Object* object) {

	Object* nearest = NULL;

	/*
	for (list<Object*>::iterator itr = m_active.begin(); itr != m_active.end(); itr++)

		if ((*itr) != object) {

			nearest = (*itr);

			break;
		}

	if (nearest) {

		for (list<Object*>::iterator itr = m_active.begin(); itr != m_active.end(); itr++)

			if (((*itr) != nearest) && ((*itr) != object))

				if ((((*itr)->getPosition() - object->getPosition()).squaredLength()) < ((nearest->getPosition() - object->getPosition()).squaredLength()))

					nearest = (*itr);
	}
	//*/

	return nearest;
}

//------------------------------------------------------------------------------

void ObjectManager::update(float deltaTime) {

	for (list<Building*>::iterator itr = m_building.m_active.begin(); itr != m_building.m_active.end(); itr++)

		(*itr)->update(deltaTime);

	for (list<Object*>::iterator itr = m_object.m_active.begin(); itr != m_object.m_active.end(); itr++)

		(*itr)->update(deltaTime);

	for (list<Projectile*>::iterator itr = m_projectile.m_active.begin(); itr != m_projectile.m_active.end(); itr++)

		(*itr)->update(deltaTime);

	for (list<Unit*>::iterator itr = m_unit.m_active.begin(); itr != m_unit.m_active.end(); itr++)

		(*itr)->update(deltaTime);
}

//------------------------------------------------------------------------------
