
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ObjectManager.h"

#include "PartManager.h"

//------------------------------------------------------------------------------

Object* ObjectManager::create(const string& name, ObjectDesc* objectDesc) {

	Object* object = ResourceManager::create(name);

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

void ObjectManager::getAllInRadius(List& list, Ogre::Vector3 point, float radius) {

	for (Iterator itr = m_active.begin(); itr != m_active.end(); itr++)

		if (((*itr)->getPosition() - point).length() <= radius)

			list.push_back(*itr);
}

//------------------------------------------------------------------------------

Object* ObjectManager::getNearest(Object* object) {

	Object* nearest = NULL;

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

	return nearest;
}

//------------------------------------------------------------------------------

void ObjectManager::update(float deltaTime) {

	for (list<Object*>::iterator itr = m_active.begin(); itr != m_active.end(); itr++)

		(*itr)->update(deltaTime);
}

//------------------------------------------------------------------------------
