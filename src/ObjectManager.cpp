
//------------------------------------------------------------------------------
// ObjectManager.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "Building.h"
#include "BuildingDesc.h"
#include "Fortification.h"
#include "FortificationDesc.h"
#include "ObjectDesc.h"
#include "ObjectManager.h"
#include "Plant.h"
#include "PlantDesc.h"
#include "PowerPlant.h"
#include "PowerPlantDesc.h"
#include "Vehicle.h"
#include "VehicleDesc.h"

//------------------------------------------------------------------------------

void ObjectManager::add(Object* object) {

	m_list.push_back(object);
}

//------------------------------------------------------------------------------

Object* ObjectManager::create(ObjectDesc* objectDesc, Player* player, const Vector3& position) {

	if (objectDesc && player) {

		switch (objectDesc->m_type) {

			//
			// Plant
			//

			case ObjectDesc::ODT_PLANT_DESC:

				{
					Plant* p = new Plant();

					p->m_body->setDesc(objectDesc->m_bodyDesc);
					p->setPosition(position);
					p->setPlayer(player);

					m_list.push_back(p);

					return p;
				}

			//
			// Object
			//

			case ObjectDesc::ODT_OBJECT_DESC:

				{
					Object* o = new Object();

					o->m_body->setDesc(objectDesc->m_bodyDesc);
					o->setPosition(position);
					o->setPlayer(player);

					m_list.push_back(o);

					return o;
				}

			//
			// Building
			//

			case ObjectDesc::ODT_BUILDING_DESC:

				{
					Building* b = new Building();

					b->m_body->setDesc(objectDesc->m_bodyDesc);
					b->m_armour->setDesc(objectDesc->isBuildingDesc()->m_armourDesc);
					b->setPosition(position);
					b->setPlayer(player);

					m_list.push_back(b);

					return b;
				}

			//
			// Power Plant
			//

			case ObjectDesc::ODT_POWER_PLANT_DESC:

				{
					PowerPlant* p = new PowerPlant();

					p->m_body->setDesc(objectDesc->m_bodyDesc);
					p->m_armour->setDesc(objectDesc->isPowerPlantDesc()->m_armourDesc);
					p->m_reactor->setDesc(objectDesc->isPowerPlantDesc()->m_powerReactorDesc);
					p->setPosition(position);
					p->setPlayer(player);

					m_list.push_back(p);

					return p;
				}

			//
			// Fortification
			//

			case ObjectDesc::ODT_FORTIFICATION_DESC:

				{
					Fortification* f = new Fortification();

					f->m_body->setDesc(objectDesc->m_bodyDesc);
					f->m_armour->setDesc(objectDesc->isFortificationDesc()->m_armourDesc);
					f->m_weapon->setDesc(objectDesc->isFortificationDesc()->m_weaponDesc);
					f->setPosition(position);
					f->setPlayer(player);

					m_list.push_back(f);

					return f;
				}

			//
			// Vehicle
			//

			case ObjectDesc::ODT_VEHICLE_DESC:

				{
					Vehicle* v = new Vehicle();

					v->m_body->setDesc(objectDesc->m_bodyDesc);
					v->m_armour->setDesc(objectDesc->isVehicleDesc()->m_armourDesc);
					v->m_shield->setDesc(objectDesc->isVehicleDesc()->m_energyShieldDesc);
					v->m_engine->setDesc(objectDesc->isVehicleDesc()->m_engineDesc);
					v->m_weapon->setDesc(objectDesc->isVehicleDesc()->m_weaponDesc);
					v->setPosition(position);
					v->setPlayer(player);

					m_list.push_back(v);

					return v;
				}

		} // switch (objectDesc->m_type)

	} // if (objectDesc)

	return NULL;
}

//------------------------------------------------------------------------------

void ObjectManager::deselect(Object* object) {

	object->setSelected(false);

	m_selected.remove(object);

}

//------------------------------------------------------------------------------

void ObjectManager::deselectAll() {

	for (Iterator itr = m_selected.begin(); itr != m_selected.end(); itr++)

		(*itr)->setSelected(false);

	m_selected.clear();

}

//------------------------------------------------------------------------------

ObjectManager::Iterator ObjectManager::getFirst() {

	return m_list.begin();

}

//------------------------------------------------------------------------------

ObjectManager::Iterator ObjectManager::getLast() {

	return m_list.end();

}

//------------------------------------------------------------------------------

void ObjectManager::getAllInRadius(Object* object, float radius, List* allInRadius) {

	for (Iterator itr = m_list.begin(); itr != m_list.end(); itr++)

		if (((*itr) != object) && ((object->getPosition() - (*itr)->getPosition()).length()) <= radius)

			(*allInRadius).push_back(*itr);

}

//------------------------------------------------------------------------------

Object* ObjectManager::getNearest(Object* object) {

	Object* nearest = NULL;

	for (list<Object*>::iterator itr = m_list.begin(); itr != m_list.end(); itr++)

		if ((*itr) != object) {

			nearest = (*itr);

			break;
		}

	if (nearest) {

		for (list<Object*>::iterator itr = m_list.begin(); itr != m_list.end(); itr++)

			if (((*itr) != nearest) && ((*itr) != object))

				if ((((*itr)->getPosition() - object->getPosition()).squaredLength()) < ((nearest->getPosition() - object->getPosition()).squaredLength()))

					nearest = (*itr);

		return nearest;
	}

	return NULL;
}

//------------------------------------------------------------------------------

Object* ObjectManager::getNearestEnemy(Object* object) {

	Object* nearest = NULL;

	for (list<Object*>::iterator itr = m_list.begin(); itr != m_list.end(); itr++)

		if (((*itr) != object) && (*itr)->isEnemy(object) && ((*itr)->m_type != Object::OT_MISSILE)) {

			nearest = (*itr);

			break;
		}

	if (nearest) {

		for (list<Object*>::iterator itr = m_list.begin(); itr != m_list.end(); itr++)

			if (((*itr) != object) && ((*itr) != nearest) && ((*itr)->isEnemy(object)) && ((*itr)->m_type != Object::OT_MISSILE) && ((*itr)->m_state != Object::OS_DEAD))

				if ((((*itr)->getPosition() - object->getPosition()).squaredLength()) < ((nearest->getPosition() - object->getPosition()).squaredLength()))

					nearest = (*itr);

		return nearest;
	}

	return NULL;
}

//------------------------------------------------------------------------------

void ObjectManager::select(Object* object) {

	object->setSelected(true);

	m_selected.push_back(object);
}

//------------------------------------------------------------------------------

void ObjectManager::selecteAll() {

	for (Iterator itr = m_list.begin(); itr != m_list.end(); itr++)

		(*itr)->setSelected(true);

	m_selected = m_list;
}

//------------------------------------------------------------------------------

void ObjectManager::update(float deltaTime) {

	static List toDestroy;

	for (Iterator itr = m_list.begin(); itr != m_list.end(); itr++)

		if ((*itr)->update(deltaTime) == false)

			toDestroy.push_back(*itr);

	for (Iterator itr = toDestroy.begin(); itr != toDestroy.end(); itr++)

		destroy(*itr);

	toDestroy.clear();
}

//------------------------------------------------------------------------------
