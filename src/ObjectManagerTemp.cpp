
//------------------------------------------------------------------------------
// ObjectManagerTemp.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Building.h"
#include "BuildingDesc.h"
#include "Fortification.h"
#include "FortificationDesc.h"
#include "ObjectDesc.h"
#include "ObjectManagerTemp.h"
#include "Plant.h"
#include "PlantDesc.h"
#include "PowerPlant.h"
#include "PowerPlantDesc.h"
#include "Vehicle.h"
#include "VehicleDesc.h"

//------------------------------------------------------------------------------

void ObjectManagerTemp::add(ObjectTemp* object) {

	m_list.push_back(object);
}

//------------------------------------------------------------------------------

ObjectTemp* ObjectManagerTemp::create(ObjectDesc* objectDesc, Player* player, const Vector3& position) {

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
			// ObjectTemp
			//

			case ObjectDesc::ODT_OBJECT_DESC:

				{
					ObjectTemp* o = new ObjectTemp();

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
					p->m_powerReactor->setDesc(objectDesc->isPowerPlantDesc()->m_powerReactorDesc);
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

void ObjectManagerTemp::deselect(ObjectTemp* object) {

	object->setSelected(false);

	m_selected.remove(object);

}

//------------------------------------------------------------------------------

void ObjectManagerTemp::deselectAll() {

	for (Iterator itr = m_selected.begin(); itr != m_selected.end(); itr++)

		(*itr)->setSelected(false);

	m_selected.clear();

}

//------------------------------------------------------------------------------

ObjectManagerTemp::Iterator ObjectManagerTemp::getFirst() {

	return m_list.begin();

}

//------------------------------------------------------------------------------

ObjectManagerTemp::Iterator ObjectManagerTemp::getLast() {

	return m_list.end();

}

//------------------------------------------------------------------------------

void ObjectManagerTemp::getAllInRadius(ObjectTemp* object, float radius, List* allInRadius) {

	for (Iterator itr = m_list.begin(); itr != m_list.end(); itr++)

		if (((*itr) != object) && ((object->getPosition() - (*itr)->getPosition()).length()) <= radius)

			(*allInRadius).push_back(*itr);

}

//------------------------------------------------------------------------------

ObjectTemp* ObjectManagerTemp::getNearest(ObjectTemp* object) {

	ObjectTemp* nearest = NULL;

	for (list<ObjectTemp*>::iterator itr = m_list.begin(); itr != m_list.end(); itr++)

		if ((*itr) != object) {

			nearest = (*itr);

			break;
		}

	if (nearest) {

		for (list<ObjectTemp*>::iterator itr = m_list.begin(); itr != m_list.end(); itr++)

			if (((*itr) != nearest) && ((*itr) != object))

				if ((((*itr)->getPosition() - object->getPosition()).squaredLength()) < ((nearest->getPosition() - object->getPosition()).squaredLength()))

					nearest = (*itr);

		return nearest;
	}

	return NULL;
}

//------------------------------------------------------------------------------

ObjectTemp* ObjectManagerTemp::getNearestEnemy(ObjectTemp* object) {

	ObjectTemp* nearest = NULL;

	for (list<ObjectTemp*>::iterator itr = m_list.begin(); itr != m_list.end(); itr++)

		if (((*itr) != object) && (*itr)->isEnemy(object) && ((*itr)->m_type != ObjectTemp::OT_MISSILE)) {

			nearest = (*itr);

			break;
		}

	if (nearest) {

		for (list<ObjectTemp*>::iterator itr = m_list.begin(); itr != m_list.end(); itr++)

			if (((*itr) != object) && ((*itr) != nearest) && ((*itr)->isEnemy(object)) && ((*itr)->m_type != ObjectTemp::OT_MISSILE) && ((*itr)->m_state != ObjectTemp::OS_DEAD))

				if ((((*itr)->getPosition() - object->getPosition()).squaredLength()) < ((nearest->getPosition() - object->getPosition()).squaredLength()))

					nearest = (*itr);

		return nearest;
	}

	return NULL;
}

//------------------------------------------------------------------------------

void ObjectManagerTemp::select(ObjectTemp* object) {

	object->setSelected(true);

	m_selected.push_back(object);
}

//------------------------------------------------------------------------------

void ObjectManagerTemp::selecteAll() {

	for (Iterator itr = m_list.begin(); itr != m_list.end(); itr++)

		(*itr)->setSelected(true);

	m_selected = m_list;
}

//------------------------------------------------------------------------------

void ObjectManagerTemp::update(float deltaTime) {

	static List toDestroy;

	for (Iterator itr = m_list.begin(); itr != m_list.end(); itr++)

		if ((*itr)->update(deltaTime) == false)

			toDestroy.push_back(*itr);

	for (Iterator itr = toDestroy.begin(); itr != toDestroy.end(); itr++)

		destroy(*itr);

	toDestroy.clear();
}

//------------------------------------------------------------------------------
